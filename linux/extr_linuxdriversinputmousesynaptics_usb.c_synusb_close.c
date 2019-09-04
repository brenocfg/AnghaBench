#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct synusb {int is_open; TYPE_1__* intf; int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  urb; } ;
struct input_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ needs_remote_wakeup; } ;

/* Variables and functions */
 struct synusb* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void synusb_close(struct input_dev *dev)
{
	struct synusb *synusb = input_get_drvdata(dev);
	int autopm_error;

	autopm_error = usb_autopm_get_interface(synusb->intf);

	mutex_lock(&synusb->pm_mutex);
	usb_kill_urb(synusb->urb);
	synusb->intf->needs_remote_wakeup = 0;
	synusb->is_open = false;
	mutex_unlock(&synusb->pm_mutex);

	if (!autopm_error)
		usb_autopm_put_interface(synusb->intf);
}