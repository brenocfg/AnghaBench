#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbtouch_usb {int is_open; TYPE_2__* interface; int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  irq; TYPE_1__* type; } ;
struct input_dev {int dummy; } ;
struct TYPE_5__ {scalar_t__ needs_remote_wakeup; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq_always; } ;

/* Variables and functions */
 struct usbtouch_usb* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbtouch_close(struct input_dev *input)
{
	struct usbtouch_usb *usbtouch = input_get_drvdata(input);
	int r;

	mutex_lock(&usbtouch->pm_mutex);
	if (!usbtouch->type->irq_always)
		usb_kill_urb(usbtouch->irq);
	usbtouch->is_open = false;
	mutex_unlock(&usbtouch->pm_mutex);

	r = usb_autopm_get_interface(usbtouch->interface);
	usbtouch->interface->needs_remote_wakeup = 0;
	if (!r)
		usb_autopm_put_interface(usbtouch->interface);
}