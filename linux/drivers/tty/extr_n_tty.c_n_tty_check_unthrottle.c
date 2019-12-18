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
struct tty_struct {int /*<<< orphan*/  link; TYPE_1__* driver; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ TTY_DRIVER_TYPE_PTY ; 
 scalar_t__ TTY_THRESHOLD_UNTHROTTLE ; 
 int /*<<< orphan*/  TTY_UNTHROTTLE_SAFE ; 
 int /*<<< orphan*/  __tty_set_flow_change (struct tty_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ chars_in_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  n_tty_kick_worker (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_set_flow_change (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int tty_unthrottle_safe (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void n_tty_check_unthrottle(struct tty_struct *tty)
{
	if (tty->driver->type == TTY_DRIVER_TYPE_PTY) {
		if (chars_in_buffer(tty) > TTY_THRESHOLD_UNTHROTTLE)
			return;
		n_tty_kick_worker(tty);
		tty_wakeup(tty->link);
		return;
	}

	/* If there is enough space in the read buffer now, let the
	 * low-level driver know. We use chars_in_buffer() to
	 * check the buffer, as it now knows about canonical mode.
	 * Otherwise, if the driver is throttled and the line is
	 * longer than TTY_THRESHOLD_UNTHROTTLE in canonical mode,
	 * we won't get any more characters.
	 */

	while (1) {
		int unthrottled;
		tty_set_flow_change(tty, TTY_UNTHROTTLE_SAFE);
		if (chars_in_buffer(tty) > TTY_THRESHOLD_UNTHROTTLE)
			break;
		n_tty_kick_worker(tty);
		unthrottled = tty_unthrottle_safe(tty);
		if (!unthrottled)
			break;
	}
	__tty_set_flow_change(tty, 0);
}