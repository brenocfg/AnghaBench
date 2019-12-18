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
struct TYPE_2__ {scalar_t__ tty; } ;
struct ipw_tty {unsigned int control_lines; TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int IPW_CONTROL_LINE_DCD ; 
 int /*<<< orphan*/  tty_hangup (scalar_t__) ; 

void
ipwireless_tty_notify_control_line_change(struct ipw_tty *tty,
					  unsigned int channel_idx,
					  unsigned int control_lines,
					  unsigned int changed_mask)
{
	unsigned int old_control_lines = tty->control_lines;

	tty->control_lines = (tty->control_lines & ~changed_mask)
		| (control_lines & changed_mask);

	/*
	 * If DCD is de-asserted, we close the tty so pppd can tell that we
	 * have gone offline.
	 */
	if ((old_control_lines & IPW_CONTROL_LINE_DCD)
			&& !(tty->control_lines & IPW_CONTROL_LINE_DCD)
			&& tty->port.tty) {
		tty_hangup(tty->port.tty);
	}
}