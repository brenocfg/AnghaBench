#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; } ;
struct TYPE_8__ {scalar_t__ state; int dir_in; int /*<<< orphan*/  ctlstat; int /*<<< orphan*/  setup; } ;
struct ast_vhub_ep {scalar_t__ d_idx; TYPE_4__ ep0; TYPE_3__* vhub; TYPE_2__* dev; } ;
typedef  enum std_req_rc { ____Placeholder_std_req_rc } std_req_rc ;
typedef  int /*<<< orphan*/  crq ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
struct TYPE_5__ {int (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  EPDBG (struct ast_vhub_ep*,char*,...) ; 
 int /*<<< orphan*/  EPVDBG (struct ast_vhub_ep*,char*) ; 
 int USB_DIR_IN ; 
 int USB_TYPE_CLASS ; 
 int USB_TYPE_MASK ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  VHUB_EP0_CTRL_STALL ; 
 int /*<<< orphan*/  VHUB_EP0_TX_BUFF_RDY ; 
 scalar_t__ WARN_ON (int) ; 
 int ast_vhub_class_hub_request (struct ast_vhub_ep*,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  ast_vhub_nuke (struct ast_vhub_ep*,int /*<<< orphan*/ ) ; 
 int ast_vhub_std_dev_request (struct ast_vhub_ep*,struct usb_ctrlrequest*) ; 
 int ast_vhub_std_hub_request (struct ast_vhub_ep*,struct usb_ctrlrequest*) ; 
 scalar_t__ ep0_state_data ; 
 scalar_t__ ep0_state_stall ; 
 scalar_t__ ep0_state_status ; 
 scalar_t__ ep0_state_token ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (struct usb_ctrlrequest*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
#define  std_req_complete 131 
#define  std_req_data 130 
#define  std_req_driver 129 
#define  std_req_stall 128 
 int stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ast_vhub_ep0_handle_setup(struct ast_vhub_ep *ep)
{
	struct usb_ctrlrequest crq;
	enum std_req_rc std_req_rc;
	int rc = -ENODEV;

	if (WARN_ON(ep->d_idx != 0))
		return;

	/*
	 * Grab the setup packet from the chip and byteswap
	 * interesting fields
	 */
	memcpy_fromio(&crq, ep->ep0.setup, sizeof(crq));

	EPDBG(ep, "SETUP packet %02x/%02x/%04x/%04x/%04x [%s] st=%d\n",
	      crq.bRequestType, crq.bRequest,
	       le16_to_cpu(crq.wValue),
	       le16_to_cpu(crq.wIndex),
	       le16_to_cpu(crq.wLength),
	       (crq.bRequestType & USB_DIR_IN) ? "in" : "out",
	       ep->ep0.state);

	/*
	 * Check our state, cancel pending requests if needed
	 *
	 * Note: Under some circumstances, we can get a new setup
	 * packet while waiting for the stall ack, just accept it.
	 *
	 * In any case, a SETUP packet in wrong state should have
	 * reset the HW state machine, so let's just log, nuke
	 * requests, move on.
	 */
	if (ep->ep0.state != ep0_state_token &&
	    ep->ep0.state != ep0_state_stall) {
		EPDBG(ep, "wrong state\n");
		ast_vhub_nuke(ep, -EIO);
	}

	/* Calculate next state for EP0 */
	ep->ep0.state = ep0_state_data;
	ep->ep0.dir_in = !!(crq.bRequestType & USB_DIR_IN);

	/* If this is the vHub, we handle requests differently */
	std_req_rc = std_req_driver;
	if (ep->dev == NULL) {
		if ((crq.bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
			std_req_rc = ast_vhub_std_hub_request(ep, &crq);
		else if ((crq.bRequestType & USB_TYPE_MASK) == USB_TYPE_CLASS)
			std_req_rc = ast_vhub_class_hub_request(ep, &crq);
		else
			std_req_rc = std_req_stall;
	} else if ((crq.bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		std_req_rc = ast_vhub_std_dev_request(ep, &crq);

	/* Act upon result */
	switch(std_req_rc) {
	case std_req_complete:
		goto complete;
	case std_req_stall:
		goto stall;
	case std_req_driver:
		break;
	case std_req_data:
		return;
	}

	/* Pass request up to the gadget driver */
	if (WARN_ON(!ep->dev))
		goto stall;
	if (ep->dev->driver) {
		EPDBG(ep, "forwarding to gadget...\n");
		spin_unlock(&ep->vhub->lock);
		rc = ep->dev->driver->setup(&ep->dev->gadget, &crq);
		spin_lock(&ep->vhub->lock);
		EPDBG(ep, "driver returned %d\n", rc);
	} else {
		EPDBG(ep, "no gadget for request !\n");
	}
	if (rc >= 0)
		return;

 stall:
	EPDBG(ep, "stalling\n");
	writel(VHUB_EP0_CTRL_STALL, ep->ep0.ctlstat);
	ep->ep0.state = ep0_state_stall;
	ep->ep0.dir_in = false;
	return;

 complete:
	EPVDBG(ep, "sending [in] status with no data\n");
	writel(VHUB_EP0_TX_BUFF_RDY, ep->ep0.ctlstat);
	ep->ep0.state = ep0_state_status;
	ep->ep0.dir_in = false;
}