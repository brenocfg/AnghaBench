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
struct ipw_network {int /*<<< orphan*/ *** associated_ttys; } ;

/* Variables and functions */
 int MAX_ASSOCIATED_TTYS ; 

void ipwireless_disassociate_network_ttys(struct ipw_network *network,
					  unsigned int channel_idx)
{
	int i;

	for (i = 0; i < MAX_ASSOCIATED_TTYS; i++)
		network->associated_ttys[channel_idx][i] = NULL;
}