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
struct usb_gadget {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* wakeup ) (struct usb_gadget*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct usb_gadget*) ; 
 int /*<<< orphan*/  trace_usb_gadget_wakeup (struct usb_gadget*,int) ; 

int usb_gadget_wakeup(struct usb_gadget *gadget)
{
	int ret = 0;

	if (!gadget->ops->wakeup) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	ret = gadget->ops->wakeup(gadget);

out:
	trace_usb_gadget_wakeup(gadget, ret);

	return ret;
}