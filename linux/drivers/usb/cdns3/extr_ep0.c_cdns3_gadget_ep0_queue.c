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
typedef  int u8 ;
struct usb_request {int length; int /*<<< orphan*/  dma; scalar_t__ zero; int /*<<< orphan*/  list; int /*<<< orphan*/  status; scalar_t__ actual; } ;
struct usb_ep {int maxpacket; } ;
struct cdns3_endpoint {int /*<<< orphan*/  pending_req_list; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {scalar_t__ ep0_stage; int status_completion_no_call; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  ep0_data_dir; int /*<<< orphan*/  sysdev; int /*<<< orphan*/  pending_status_wq; struct usb_request* pending_status_request; int /*<<< orphan*/  hw_configured_flag; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ CDNS3_STATUS_STAGE ; 
 int EBUSY ; 
 int ECONNRESET ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  cdns3_allow_enable_l1 (struct cdns3_device*,int) ; 
 scalar_t__ cdns3_check_new_setup (struct cdns3_device*) ; 
 int /*<<< orphan*/  cdns3_ep0_complete_setup (struct cdns3_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdns3_ep0_run_transfer (struct cdns3_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  cdns3_select_ep (struct cdns3_device*,int) ; 
 int /*<<< orphan*/  cdns3_set_hw_configuration (struct cdns3_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct cdns3_endpoint* ep_to_cdns3_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_freezable_wq ; 
 int /*<<< orphan*/  trace_cdns3_ep0_queue (struct cdns3_device*,struct usb_request*) ; 
 int usb_gadget_map_request_by_dev (int /*<<< orphan*/ ,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns3_gadget_ep0_queue(struct usb_ep *ep,
				  struct usb_request *request,
				  gfp_t gfp_flags)
{
	struct cdns3_endpoint *priv_ep = ep_to_cdns3_ep(ep);
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;
	unsigned long flags;
	int erdy_sent = 0;
	int ret = 0;
	u8 zlp = 0;

	trace_cdns3_ep0_queue(priv_dev, request);

	/* cancel the request if controller receive new SETUP packet. */
	if (cdns3_check_new_setup(priv_dev))
		return -ECONNRESET;

	/* send STATUS stage. Should be called only for SET_CONFIGURATION */
	if (priv_dev->ep0_stage == CDNS3_STATUS_STAGE) {
		spin_lock_irqsave(&priv_dev->lock, flags);
		cdns3_select_ep(priv_dev, 0x00);

		erdy_sent = !priv_dev->hw_configured_flag;
		cdns3_set_hw_configuration(priv_dev);

		if (!erdy_sent)
			cdns3_ep0_complete_setup(priv_dev, 0, 1);

		cdns3_allow_enable_l1(priv_dev, 1);

		request->actual = 0;
		priv_dev->status_completion_no_call = true;
		priv_dev->pending_status_request = request;
		spin_unlock_irqrestore(&priv_dev->lock, flags);

		/*
		 * Since there is no completion interrupt for status stage,
		 * it needs to call ->completion in software after
		 * ep0_queue is back.
		 */
		queue_work(system_freezable_wq, &priv_dev->pending_status_wq);
		return 0;
	}

	spin_lock_irqsave(&priv_dev->lock, flags);
	if (!list_empty(&priv_ep->pending_req_list)) {
		dev_err(priv_dev->dev,
			"can't handle multiple requests for ep0\n");
		spin_unlock_irqrestore(&priv_dev->lock, flags);
		return -EBUSY;
	}

	ret = usb_gadget_map_request_by_dev(priv_dev->sysdev, request,
					    priv_dev->ep0_data_dir);
	if (ret) {
		spin_unlock_irqrestore(&priv_dev->lock, flags);
		dev_err(priv_dev->dev, "failed to map request\n");
		return -EINVAL;
	}

	request->status = -EINPROGRESS;
	list_add_tail(&request->list, &priv_ep->pending_req_list);

	if (request->zero && request->length &&
	    (request->length % ep->maxpacket == 0))
		zlp = 1;

	cdns3_ep0_run_transfer(priv_dev, request->dma, request->length, 1, zlp);

	spin_unlock_irqrestore(&priv_dev->lock, flags);

	return ret;
}