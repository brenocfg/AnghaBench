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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u16 ;
struct usb_request {unsigned int length; struct usb_cdc_notification* buf; } ;
struct usb_ep {int dummy; } ;
struct usb_cdc_notification {int bmRequestType; void* wLength; void* wIndex; void* wValue; int /*<<< orphan*/  bNotificationType; } ;
struct TYPE_5__ {TYPE_1__* config; } ;
struct TYPE_6__ {TYPE_2__ func; } ;
struct f_acm {int pending; unsigned int ctrl_id; struct usb_request* notify_req; int /*<<< orphan*/  port_num; TYPE_3__ port; int /*<<< orphan*/  lock; struct usb_ep* notify; } ;
struct TYPE_4__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int usb_ep_queue (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acm_cdc_notify(struct f_acm *acm, u8 type, u16 value,
		void *data, unsigned length)
{
	struct usb_ep			*ep = acm->notify;
	struct usb_request		*req;
	struct usb_cdc_notification	*notify;
	const unsigned			len = sizeof(*notify) + length;
	void				*buf;
	int				status;

	req = acm->notify_req;
	acm->notify_req = NULL;
	acm->pending = false;

	req->length = len;
	notify = req->buf;
	buf = notify + 1;

	notify->bmRequestType = USB_DIR_IN | USB_TYPE_CLASS
			| USB_RECIP_INTERFACE;
	notify->bNotificationType = type;
	notify->wValue = cpu_to_le16(value);
	notify->wIndex = cpu_to_le16(acm->ctrl_id);
	notify->wLength = cpu_to_le16(length);
	memcpy(buf, data, length);

	/* ep_queue() can complete immediately if it fills the fifo... */
	spin_unlock(&acm->lock);
	status = usb_ep_queue(ep, req, GFP_ATOMIC);
	spin_lock(&acm->lock);

	if (status < 0) {
		ERROR(acm->port.func.config->cdev,
				"acm ttyGS%d can't notify serial state, %d\n",
				acm->port_num, status);
		acm->notify_req = req;
	}

	return status;
}