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
typedef  int u32 ;
struct urb {int actual_length; int /*<<< orphan*/  transfer_buffer; } ;
struct TYPE_2__ {scalar_t__ phyirq; } ;
struct lan78xx_net {int /*<<< orphan*/  net; TYPE_1__ domain_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_LINK_RESET ; 
 int INT_ENP_PHY_INT ; 
 int /*<<< orphan*/  generic_handle_irq (scalar_t__) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan78xx_defer_kevent (struct lan78xx_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_dbg (struct lan78xx_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void lan78xx_status(struct lan78xx_net *dev, struct urb *urb)
{
	u32 intdata;

	if (urb->actual_length != 4) {
		netdev_warn(dev->net,
			    "unexpected urb length %d", urb->actual_length);
		return;
	}

	intdata = get_unaligned_le32(urb->transfer_buffer);

	if (intdata & INT_ENP_PHY_INT) {
		netif_dbg(dev, link, dev->net, "PHY INTR: 0x%08x\n", intdata);
		lan78xx_defer_kevent(dev, EVENT_LINK_RESET);

		if (dev->domain_data.phyirq > 0) {
			local_irq_disable();
			generic_handle_irq(dev->domain_data.phyirq);
			local_irq_enable();
		}
	} else
		netdev_warn(dev->net,
			    "unexpected interrupt: 0x%08x\n", intdata);
}