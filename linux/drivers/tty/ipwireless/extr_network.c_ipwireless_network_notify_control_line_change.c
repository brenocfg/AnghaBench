#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ipw_tty {int dummy; } ;
struct ipw_network {unsigned int ras_control_lines; struct ipw_tty*** associated_ttys; } ;

/* Variables and functions */
 unsigned int IPW_CHANNEL_RAS ; 
 int MAX_ASSOCIATED_TTYS ; 
 int /*<<< orphan*/  ipwireless_tty_notify_control_line_change (struct ipw_tty*,unsigned int,unsigned int,unsigned int) ; 

void ipwireless_network_notify_control_line_change(struct ipw_network *network,
						   unsigned int channel_idx,
						   unsigned int control_lines,
						   unsigned int changed_mask)
{
	int i;

	if (channel_idx == IPW_CHANNEL_RAS)
		network->ras_control_lines = control_lines;

	for (i = 0; i < MAX_ASSOCIATED_TTYS; i++) {
		struct ipw_tty *tty =
			network->associated_ttys[channel_idx][i];

		/*
		 * If it's associated with a tty (other than the RAS channel
		 * when we're online), then send the data to that tty.  The RAS
		 * channel's data is handled above - it always goes through
		 * ppp_generic.
		 */
		if (tty)
			ipwireless_tty_notify_control_line_change(tty,
								  channel_idx,
								  control_lines,
								  changed_mask);
	}
}