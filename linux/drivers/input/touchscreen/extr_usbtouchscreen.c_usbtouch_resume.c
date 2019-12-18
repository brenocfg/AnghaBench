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
struct usbtouch_usb {int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  irq; TYPE_1__* type; scalar_t__ is_open; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {scalar_t__ irq_always; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usbtouch_usb* usb_get_intfdata (struct usb_interface*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbtouch_resume(struct usb_interface *intf)
{
	struct usbtouch_usb *usbtouch = usb_get_intfdata(intf);
	int result = 0;

	mutex_lock(&usbtouch->pm_mutex);
	if (usbtouch->is_open || usbtouch->type->irq_always)
		result = usb_submit_urb(usbtouch->irq, GFP_NOIO);
	mutex_unlock(&usbtouch->pm_mutex);

	return result;
}