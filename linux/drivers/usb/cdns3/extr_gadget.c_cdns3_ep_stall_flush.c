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
struct cdns3_endpoint {int /*<<< orphan*/  flags; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_cmd; } ;

/* Variables and functions */
 int EP_CMD_DFLUSH ; 
 int EP_CMD_ERDY ; 
 int EP_CMD_SSTALL ; 
 int /*<<< orphan*/  EP_STALLED ; 
 int /*<<< orphan*/  EP_STALL_PENDING ; 
 int /*<<< orphan*/  readl_poll_timeout_atomic (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  trace_cdns3_halt (struct cdns3_endpoint*,int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdns3_ep_stall_flush(struct cdns3_endpoint *priv_ep)
{
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;
	int val;

	trace_cdns3_halt(priv_ep, 1, 1);

	writel(EP_CMD_DFLUSH | EP_CMD_ERDY | EP_CMD_SSTALL,
	       &priv_dev->regs->ep_cmd);

	/* wait for DFLUSH cleared */
	readl_poll_timeout_atomic(&priv_dev->regs->ep_cmd, val,
				  !(val & EP_CMD_DFLUSH), 1, 1000);
	priv_ep->flags |= EP_STALLED;
	priv_ep->flags &= ~EP_STALL_PENDING;
}