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
struct usb_gadget {int connected; TYPE_1__* ops; scalar_t__ deactivated; } ;
struct TYPE_2__ {int (* pullup ) (struct usb_gadget*,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct usb_gadget*,int) ; 
 int /*<<< orphan*/  trace_usb_gadget_connect (struct usb_gadget*,int) ; 

int usb_gadget_connect(struct usb_gadget *gadget)
{
	int ret = 0;

	if (!gadget->ops->pullup) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	if (gadget->deactivated) {
		/*
		 * If gadget is deactivated we only save new state.
		 * Gadget will be connected automatically after activation.
		 */
		gadget->connected = true;
		goto out;
	}

	ret = gadget->ops->pullup(gadget, 1);
	if (!ret)
		gadget->connected = 1;

out:
	trace_usb_gadget_connect(gadget, ret);

	return ret;
}