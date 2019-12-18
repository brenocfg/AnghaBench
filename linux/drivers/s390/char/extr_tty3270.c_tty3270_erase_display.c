#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rows; } ;
struct tty3270 {int cy; TYPE_2__* screen; TYPE_1__ view; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty3270_convert_line (struct tty3270*,int) ; 
 int /*<<< orphan*/  tty3270_erase_line (struct tty3270*,int) ; 
 int /*<<< orphan*/  tty3270_rebuild_update (struct tty3270*) ; 

__attribute__((used)) static void
tty3270_erase_display(struct tty3270 *tp, int mode)
{
	int i;

	if (mode == 0) {
		tty3270_erase_line(tp, 0);
		for (i = tp->cy + 1; i < tp->view.rows - 2; i++) {
			tp->screen[i].len = 0;
			tty3270_convert_line(tp, i);
		}
	} else if (mode == 1) {
		for (i = 0; i < tp->cy; i++) {
			tp->screen[i].len = 0;
			tty3270_convert_line(tp, i);
		}
		tty3270_erase_line(tp, 1);
	} else if (mode == 2) {
		for (i = 0; i < tp->view.rows - 2; i++) {
			tp->screen[i].len = 0;
			tty3270_convert_line(tp, i);
		}
	}
	tty3270_rebuild_update(tp);
}