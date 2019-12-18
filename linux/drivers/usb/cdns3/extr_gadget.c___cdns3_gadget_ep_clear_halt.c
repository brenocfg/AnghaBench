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
struct usb_request {int dummy; } ;
struct cdns3_endpoint {int flags; int /*<<< orphan*/  pending_req_list; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 int EP_CMD_CSTALL ; 
 int EP_CMD_EPRST ; 
 int EP_STALLED ; 
 int EP_STALL_PENDING ; 
 struct usb_request* cdns3_next_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdns3_rearm_transfer (struct cdns3_endpoint*,int) ; 
 int /*<<< orphan*/  cdns3_start_all_request (struct cdns3_device*,struct cdns3_endpoint*) ; 
 int readl_poll_timeout_atomic (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  trace_cdns3_halt (struct cdns3_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

int __cdns3_gadget_ep_clear_halt(struct cdns3_endpoint *priv_ep)
{
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;
	struct usb_request *request;
	int ret;
	int val;

	trace_cdns3_halt(priv_ep, 0, 0);

	writel(EP_CMD_CSTALL | EP_CMD_EPRST, &priv_dev->regs->ep_cmd);

	/* wait for EPRST cleared */
	ret = readl_poll_timeout_atomic(&priv_dev->regs->ep_cmd, val,
					!(val & EP_CMD_EPRST), 1, 100);
	if (ret)
		return -EINVAL;

	priv_ep->flags &= ~(EP_STALLED | EP_STALL_PENDING);

	request = cdns3_next_request(&priv_ep->pending_req_list);

	if (request)
		cdns3_rearm_transfer(priv_ep, 1);

	cdns3_start_all_request(priv_dev, priv_ep);
	return ret;
}