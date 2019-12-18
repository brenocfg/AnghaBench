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
struct asix_rx_fixup_info {int split_head; scalar_t__ header; scalar_t__ remaining; int /*<<< orphan*/ * ax_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_asix_rx_fixup_info(struct asix_rx_fixup_info *rx)
{
	/* Reset the variables that have a lifetime outside of
	 * asix_rx_fixup_internal() so that future processing starts from a
	 * known set of initial conditions.
	 */

	if (rx->ax_skb) {
		/* Discard any incomplete Ethernet frame in the netdev buffer */
		kfree_skb(rx->ax_skb);
		rx->ax_skb = NULL;
	}

	/* Assume the Data header 32-bit word is at the start of the current
	 * or next URB socket buffer so reset all the state variables.
	 */
	rx->remaining = 0;
	rx->split_head = false;
	rx->header = 0;
}