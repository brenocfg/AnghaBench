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
struct ipw_network {struct ipw_tty*** associated_ttys; } ;

/* Variables and functions */
 int MAX_ASSOCIATED_TTYS ; 

void ipwireless_associate_network_tty(struct ipw_network *network,
				      unsigned int channel_idx,
				      struct ipw_tty *tty)
{
	int i;

	for (i = 0; i < MAX_ASSOCIATED_TTYS; i++)
		if (network->associated_ttys[channel_idx][i] == NULL) {
			network->associated_ttys[channel_idx][i] = tty;
			break;
		}
}