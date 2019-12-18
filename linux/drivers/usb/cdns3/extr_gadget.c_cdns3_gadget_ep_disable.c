#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usb_request {int dummy; } ;
struct usb_ep {TYPE_2__* desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
struct cdns3_request {int /*<<< orphan*/  list; TYPE_3__ request; } ;
struct cdns3_endpoint {int flags; int /*<<< orphan*/ * descmis_req; int /*<<< orphan*/  deferred_req_list; int /*<<< orphan*/  wa2_counter; int /*<<< orphan*/  endpoint; int /*<<< orphan*/  wa2_descmiss_req_list; int /*<<< orphan*/  pending_req_list; int /*<<< orphan*/  name; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__* regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_4__ {int /*<<< orphan*/  ep_cmd; int /*<<< orphan*/  ep_sts; int /*<<< orphan*/  ep_cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 int EP_CFG_ENABLE ; 
 int EP_CMD_CSTALL ; 
 int EP_CMD_EPRST ; 
 int EP_ENABLED ; 
 int EP_STS_DBUSY ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  cdns3_gadget_ep_free_request (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  cdns3_gadget_giveback (struct cdns3_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cdns3_request* cdns3_next_priv_request (int /*<<< orphan*/ *) ; 
 struct usb_request* cdns3_next_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdns3_select_ep (struct cdns3_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_WARN_ONCE (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct cdns3_endpoint* ep_to_cdns3_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl_poll_timeout_atomic (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  to_cdns3_request (struct usb_request*) ; 
 int /*<<< orphan*/  trace_cdns3_gadget_ep_disable (struct cdns3_endpoint*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns3_gadget_ep_disable(struct usb_ep *ep)
{
	struct cdns3_endpoint *priv_ep;
	struct cdns3_request *priv_req;
	struct cdns3_device *priv_dev;
	struct usb_request *request;
	unsigned long flags;
	int ret = 0;
	u32 ep_cfg;
	int val;

	if (!ep) {
		pr_err("usbss: invalid parameters\n");
		return -EINVAL;
	}

	priv_ep = ep_to_cdns3_ep(ep);
	priv_dev = priv_ep->cdns3_dev;

	if (dev_WARN_ONCE(priv_dev->dev, !(priv_ep->flags & EP_ENABLED),
			  "%s is already disabled\n", priv_ep->name))
		return 0;

	spin_lock_irqsave(&priv_dev->lock, flags);

	trace_cdns3_gadget_ep_disable(priv_ep);

	cdns3_select_ep(priv_dev, ep->desc->bEndpointAddress);

	ep_cfg = readl(&priv_dev->regs->ep_cfg);
	ep_cfg &= ~EP_CFG_ENABLE;
	writel(ep_cfg, &priv_dev->regs->ep_cfg);

	/**
	 * Driver needs some time before resetting endpoint.
	 * It need waits for clearing DBUSY bit or for timeout expired.
	 * 10us is enough time for controller to stop transfer.
	 */
	readl_poll_timeout_atomic(&priv_dev->regs->ep_sts, val,
				  !(val & EP_STS_DBUSY), 1, 10);
	writel(EP_CMD_EPRST, &priv_dev->regs->ep_cmd);

	readl_poll_timeout_atomic(&priv_dev->regs->ep_cmd, val,
				  !(val & (EP_CMD_CSTALL | EP_CMD_EPRST)),
				  1, 1000);
	if (unlikely(ret))
		dev_err(priv_dev->dev, "Timeout: %s resetting failed.\n",
			priv_ep->name);

	while (!list_empty(&priv_ep->pending_req_list)) {
		request = cdns3_next_request(&priv_ep->pending_req_list);

		cdns3_gadget_giveback(priv_ep, to_cdns3_request(request),
				      -ESHUTDOWN);
	}

	while (!list_empty(&priv_ep->wa2_descmiss_req_list)) {
		priv_req = cdns3_next_priv_request(&priv_ep->wa2_descmiss_req_list);

		kfree(priv_req->request.buf);
		cdns3_gadget_ep_free_request(&priv_ep->endpoint,
					     &priv_req->request);
		list_del_init(&priv_req->list);
		--priv_ep->wa2_counter;
	}

	while (!list_empty(&priv_ep->deferred_req_list)) {
		request = cdns3_next_request(&priv_ep->deferred_req_list);

		cdns3_gadget_giveback(priv_ep, to_cdns3_request(request),
				      -ESHUTDOWN);
	}

	priv_ep->descmis_req = NULL;

	ep->desc = NULL;
	priv_ep->flags &= ~EP_ENABLED;

	spin_unlock_irqrestore(&priv_dev->lock, flags);

	return ret;
}