#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty3270_line {scalar_t__ len; struct tty3270_cell* cells; } ;
struct tty3270_cell {int /*<<< orphan*/  f_color; int /*<<< orphan*/  highlight; int /*<<< orphan*/  character; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ascebc; } ;
struct tty3270 {int cy; scalar_t__ cx; int /*<<< orphan*/  f_color; int /*<<< orphan*/  highlight; TYPE_1__ view; struct tty3270_line* screen; } ;

/* Variables and functions */

__attribute__((used)) static void tty3270_put_character(struct tty3270 *tp, char ch)
{
	struct tty3270_line *line;
	struct tty3270_cell *cell;

	line = tp->screen + tp->cy;
	if (line->len <= tp->cx) {
		while (line->len < tp->cx) {
			cell = line->cells + line->len;
			cell->character = tp->view.ascebc[' '];
			cell->highlight = tp->highlight;
			cell->f_color = tp->f_color;
			line->len++;
		}
		line->len++;
	}
	cell = line->cells + tp->cx;
	cell->character = tp->view.ascebc[(unsigned int) ch];
	cell->highlight = tp->highlight;
	cell->f_color = tp->f_color;
}