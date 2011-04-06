#include <ncurses.h>
#include <cstdlib>
#include <algorithm>
#include "bucket.hpp"

int main(int argc, char *argv[])
{
	if (argc != 3)
		return 66;

	initscr();
	start_color();
	cbreak();
	keypad(stdscr, true);
	noecho();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	refresh();

	int ch = 0;
	int i;
	int cap1 = atoi(argv[1]), cap2 = atoi(argv[2]);
	const int roof = std::max(cap1, cap2) + 2 + 2;
	Bucket b1(cap1), b2(cap2);
	WINDOW *win1, *win2;

	win1 = newwin(cap1+2, 3, roof-(cap1+2), 2);
	win2 = newwin(cap2+2, 3, roof-(cap2+2), 6);

	box(win1, 0, 0);
	box(win2, 0, 0);

	wrefresh(win1);
	wrefresh(win2);
	move(0, 0);

	while (ch != 'q')
	{
		ch = getch();

		switch(ch)
		{
			case 'h':
				b1 << b2;
				break;
			case 'l':
				b1 >> b2;
				break;
			case 'u':
				b1.full();
				break;
			case 'i':
				b2.full();
				break;
			case 'j':
				b1.empty();
				break;
			case 'k':
				b2.empty();
				break;
			default:
				break;
		}
		wattron(win1, COLOR_PAIR(1));
		for (i=0; i<b1.level(); ++i)
			mvwaddch(win1, b1.max()-i, 1, ' ');
		wattroff(win1, COLOR_PAIR(1));
		for (; i<b1.max(); ++i)
			mvwaddch(win1, b1.max()-i, 1, ' ');
		wrefresh(win1);

		wattron(win2, COLOR_PAIR(1));
		for (i=0; i<b2.level(); ++i)
			mvwaddch(win2, b2.max()-i, 1, ' ');
		wattroff(win2, COLOR_PAIR(1));
		for (; i<b2.max(); ++i)
			mvwaddch(win2, b2.max()-i, 1, ' ');
		wrefresh(win2);
		move(0, 0);
	}

	endwin();
	return 0;
}