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
struct cdns3_endpoint {int flags; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_sts; } ;

/* Variables and functions */
 int EP_STALLED ; 
 int EP_STALL_PENDING ; 
 int EP_STS_DBUSY ; 
 int /*<<< orphan*/  cdns3_ep_stall_flush (struct cdns3_endpoint*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cdns3_halt (struct cdns3_endpoint*,int,int /*<<< orphan*/ ) ; 

void __cdns3_gadget_ep_set_halt(struct cdns3_endpoint *priv_ep)
{
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;

	trace_cdns3_halt(priv_ep, 1, 0);

	if (!(priv_ep->flags & EP_STALLED)) {
		u32 ep_sts_reg = readl(&priv_dev->regs->ep_sts);

		if (!(ep_sts_reg & EP_STS_DBUSY))
			cdns3_ep_stall_flush(priv_ep);
		else
			priv_ep->flags |= EP_STALL_PENDING;
	}
}