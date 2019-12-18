#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct vudc {int /*<<< orphan*/  lock; int /*<<< orphan*/  urb_queue; int /*<<< orphan*/  ud; TYPE_3__ gadget; TYPE_1__* pdev; } ;
struct TYPE_13__ {unsigned int transfer_buffer_length; unsigned int number_of_packets; } ;
struct TYPE_14__ {TYPE_4__ cmd_submit; } ;
struct TYPE_11__ {scalar_t__ direction; int /*<<< orphan*/  seqnum; int /*<<< orphan*/  ep; } ;
struct usbip_header {TYPE_5__ u; TYPE_2__ base; } ;
struct urbp {int type; int new; int /*<<< orphan*/  urb_entry; TYPE_7__* urb; TYPE_6__* ep; int /*<<< orphan*/  seqnum; } ;
struct TYPE_16__ {int pipe; int /*<<< orphan*/  status; } ;
struct TYPE_15__ {int type; int /*<<< orphan*/  desc; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int EPIPE ; 
 int PIPE_BULK ; 
 int PIPE_CONTROL ; 
 int PIPE_INTERRUPT ; 
 int PIPE_ISOCHRONOUS ; 
 scalar_t__ USBIP_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 int /*<<< orphan*/  VUDC_EVENT_ERROR_MALLOC ; 
 int /*<<< orphan*/  VUDC_EVENT_ERROR_TCP ; 
 int alloc_urb_from_cmd (TYPE_7__**,struct usbip_header*,int) ; 
 struct urbp* alloc_urbp () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free_urbp_and_urb (struct urbp*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int usb_endpoint_maxp (int /*<<< orphan*/ ) ; 
 unsigned int usb_endpoint_maxp_mult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usbip_recv_iso (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int usbip_recv_xbuff (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  v_kick_timer (struct vudc*,int /*<<< orphan*/ ) ; 
 TYPE_6__* vudc_find_endpoint (struct vudc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v_recv_cmd_submit(struct vudc *udc,
				 struct usbip_header *pdu)
{
	int ret = 0;
	struct urbp *urb_p;
	u8 address;
	unsigned long flags;

	urb_p = alloc_urbp();
	if (!urb_p) {
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_MALLOC);
		return -ENOMEM;
	}

	/* base.ep is pipeendpoint(pipe) */
	address = pdu->base.ep;
	if (pdu->base.direction == USBIP_DIR_IN)
		address |= USB_DIR_IN;

	spin_lock_irq(&udc->lock);
	urb_p->ep = vudc_find_endpoint(udc, address);
	if (!urb_p->ep) {
		/* we don't know the type, there may be isoc data! */
		dev_err(&udc->pdev->dev, "request to nonexistent endpoint");
		spin_unlock_irq(&udc->lock);
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_TCP);
		ret = -EPIPE;
		goto free_urbp;
	}
	urb_p->type = urb_p->ep->type;
	spin_unlock_irq(&udc->lock);

	urb_p->new = 1;
	urb_p->seqnum = pdu->base.seqnum;

	if (urb_p->ep->type == USB_ENDPOINT_XFER_ISOC) {
		/* validate packet size and number of packets */
		unsigned int maxp, packets, bytes;

		maxp = usb_endpoint_maxp(urb_p->ep->desc);
		maxp *= usb_endpoint_maxp_mult(urb_p->ep->desc);
		bytes = pdu->u.cmd_submit.transfer_buffer_length;
		packets = DIV_ROUND_UP(bytes, maxp);

		if (pdu->u.cmd_submit.number_of_packets < 0 ||
		    pdu->u.cmd_submit.number_of_packets > packets) {
			dev_err(&udc->gadget.dev,
				"CMD_SUBMIT: isoc invalid num packets %d\n",
				pdu->u.cmd_submit.number_of_packets);
			ret = -EMSGSIZE;
			goto free_urbp;
		}
	}

	ret = alloc_urb_from_cmd(&urb_p->urb, pdu, urb_p->ep->type);
	if (ret) {
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_MALLOC);
		ret = -ENOMEM;
		goto free_urbp;
	}

	urb_p->urb->status = -EINPROGRESS;

	/* FIXME: more pipe setup to please usbip_common */
	urb_p->urb->pipe &= ~(3 << 30);
	switch (urb_p->ep->type) {
	case USB_ENDPOINT_XFER_BULK:
		urb_p->urb->pipe |= (PIPE_BULK << 30);
		break;
	case USB_ENDPOINT_XFER_INT:
		urb_p->urb->pipe |= (PIPE_INTERRUPT << 30);
		break;
	case USB_ENDPOINT_XFER_CONTROL:
		urb_p->urb->pipe |= (PIPE_CONTROL << 30);
		break;
	case USB_ENDPOINT_XFER_ISOC:
		urb_p->urb->pipe |= (PIPE_ISOCHRONOUS << 30);
		break;
	}
	ret = usbip_recv_xbuff(&udc->ud, urb_p->urb);
	if (ret < 0)
		goto free_urbp;

	ret = usbip_recv_iso(&udc->ud, urb_p->urb);
	if (ret < 0)
		goto free_urbp;

	spin_lock_irqsave(&udc->lock, flags);
	v_kick_timer(udc, jiffies);
	list_add_tail(&urb_p->urb_entry, &udc->urb_queue);
	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;

free_urbp:
	free_urbp_and_urb(urb_p);
	return ret;
}