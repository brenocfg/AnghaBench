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
struct usb_gadget {int connected; TYPE_2__* udc; TYPE_3__* ops; scalar_t__ deactivated; } ;
struct TYPE_6__ {int (* pullup ) (struct usb_gadget*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disconnect ) (struct usb_gadget*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct usb_gadget*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct usb_gadget*) ; 
 int /*<<< orphan*/  trace_usb_gadget_disconnect (struct usb_gadget*,int) ; 

int usb_gadget_disconnect(struct usb_gadget *gadget)
{
	int ret = 0;

	if (!gadget->ops->pullup) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	if (gadget->deactivated) {
		/*
		 * If gadget is deactivated we only save new state.
		 * Gadget will stay disconnected after activation.
		 */
		gadget->connected = false;
		goto out;
	}

	ret = gadget->ops->pullup(gadget, 0);
	if (!ret) {
		gadget->connected = 0;
		gadget->udc->driver->disconnect(gadget);
	}

out:
	trace_usb_gadget_disconnect(gadget, ret);

	return ret;
}