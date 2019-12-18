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
typedef  int u32 ;
struct et131x_adapter {int packet_filter; TYPE_2__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  pf_ctrl; } ;
struct TYPE_4__ {TYPE_1__ rxmac; } ;

/* Variables and functions */
 int ET131X_PACKET_TYPE_ALL_MULTICAST ; 
 int ET131X_PACKET_TYPE_BROADCAST ; 
 int ET131X_PACKET_TYPE_DIRECTED ; 
 int ET131X_PACKET_TYPE_PROMISCUOUS ; 
 int /*<<< orphan*/  et1310_setup_device_for_multicast (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et1310_setup_device_for_unicast (struct et131x_adapter*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int et131x_set_packet_filter(struct et131x_adapter *adapter)
{
	int filter = adapter->packet_filter;
	u32 ctrl;
	u32 pf_ctrl;

	ctrl = readl(&adapter->regs->rxmac.ctrl);
	pf_ctrl = readl(&adapter->regs->rxmac.pf_ctrl);

	/* Default to disabled packet filtering */
	ctrl |= 0x04;

	/* Set us to be in promiscuous mode so we receive everything, this
	 * is also true when we get a packet filter of 0
	 */
	if ((filter & ET131X_PACKET_TYPE_PROMISCUOUS) || filter == 0)
		pf_ctrl &= ~7;	/* Clear filter bits */
	else {
		/* Set us up with Multicast packet filtering.  Three cases are
		 * possible - (1) we have a multi-cast list, (2) we receive ALL
		 * multicast entries or (3) we receive none.
		 */
		if (filter & ET131X_PACKET_TYPE_ALL_MULTICAST)
			pf_ctrl &= ~2;	/* Multicast filter bit */
		else {
			et1310_setup_device_for_multicast(adapter);
			pf_ctrl |= 2;
			ctrl &= ~0x04;
		}

		/* Set us up with Unicast packet filtering */
		if (filter & ET131X_PACKET_TYPE_DIRECTED) {
			et1310_setup_device_for_unicast(adapter);
			pf_ctrl |= 4;
			ctrl &= ~0x04;
		}

		/* Set us up with Broadcast packet filtering */
		if (filter & ET131X_PACKET_TYPE_BROADCAST) {
			pf_ctrl |= 1;	/* Broadcast filter bit */
			ctrl &= ~0x04;
		} else {
			pf_ctrl &= ~1;
		}

		/* Setup the receive mac configuration registers - Packet
		 * Filter control + the enable / disable for packet filter
		 * in the control reg.
		 */
		writel(pf_ctrl, &adapter->regs->rxmac.pf_ctrl);
		writel(ctrl, &adapter->regs->rxmac.ctrl);
	}
	return 0;
}