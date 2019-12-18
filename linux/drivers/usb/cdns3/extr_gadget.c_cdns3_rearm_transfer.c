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
typedef  scalar_t__ u8 ;
struct cdns3_endpoint {int /*<<< orphan*/  name; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_traddr; int /*<<< orphan*/  ep_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_CMD_DRDY ; 
 int /*<<< orphan*/  __cdns3_gadget_wakeup (struct cdns3_device*) ; 
 int /*<<< orphan*/  cdns3_wa1_restore_cycle_bit (struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cdns3_doorbell_epx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cdns3_ring (struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cdns3_rearm_transfer(struct cdns3_endpoint *priv_ep, u8 rearm)
{
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;

	cdns3_wa1_restore_cycle_bit(priv_ep);

	if (rearm) {
		trace_cdns3_ring(priv_ep);

		/* Cycle Bit must be updated before arming DMA. */
		wmb();
		writel(EP_CMD_DRDY, &priv_dev->regs->ep_cmd);

		__cdns3_gadget_wakeup(priv_dev);

		trace_cdns3_doorbell_epx(priv_ep->name,
					 readl(&priv_dev->regs->ep_traddr));
	}
}