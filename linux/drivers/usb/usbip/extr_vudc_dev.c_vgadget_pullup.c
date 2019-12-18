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
struct TYPE_8__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  speed; } ;
struct vudc {int pullup; int /*<<< orphan*/  lock; int /*<<< orphan*/  ud; scalar_t__ desc_cached; TYPE_4__ gadget; TYPE_3__* ep; TYPE_1__* driver; } ;
struct usb_gadget {int dummy; } ;
struct TYPE_6__ {int maxpacket; } ;
struct TYPE_7__ {TYPE_2__ ep; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  VUDC_EVENT_REMOVED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int get_gadget_descs (struct vudc*) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  u8 ; 
 struct vudc* usb_gadget_to_vudc (struct usb_gadget*) ; 
 int /*<<< orphan*/  usbip_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_start_eh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_stop_eh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vgadget_pullup(struct usb_gadget *_gadget, int value)
{
	struct vudc *udc = usb_gadget_to_vudc(_gadget);
	unsigned long flags;
	int ret;


	spin_lock_irqsave(&udc->lock, flags);
	value = !!value;
	if (value == udc->pullup)
		goto unlock;

	udc->pullup = value;
	if (value) {
		udc->gadget.speed = min_t(u8, USB_SPEED_HIGH,
					   udc->driver->max_speed);
		udc->ep[0].ep.maxpacket = 64;
		/*
		 * This is the first place where we can ask our
		 * gadget driver for descriptors.
		 */
		ret = get_gadget_descs(udc);
		if (ret) {
			dev_err(&udc->gadget.dev, "Unable go get desc: %d", ret);
			goto unlock;
		}

		spin_unlock_irqrestore(&udc->lock, flags);
		usbip_start_eh(&udc->ud);
	} else {
		/* Invalidate descriptors */
		udc->desc_cached = 0;

		spin_unlock_irqrestore(&udc->lock, flags);
		usbip_event_add(&udc->ud, VUDC_EVENT_REMOVED);
		usbip_stop_eh(&udc->ud); /* Wait for eh completion */
	}

	return 0;

unlock:
	spin_unlock_irqrestore(&udc->lock, flags);
	return 0;
}