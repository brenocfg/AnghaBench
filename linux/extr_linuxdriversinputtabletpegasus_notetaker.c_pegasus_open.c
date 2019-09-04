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
struct pegasus {int is_open; int /*<<< orphan*/  intf; int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  init; TYPE_1__* irq; int /*<<< orphan*/  usbdev; } ;
struct input_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NOTETAKER_LED_MOUSE ; 
 int /*<<< orphan*/  PEN_MODE_XY ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct pegasus* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pegasus_set_mode (struct pegasus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 
 scalar_t__ usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pegasus_open(struct input_dev *dev)
{
	struct pegasus *pegasus = input_get_drvdata(dev);
	int error;

	error = usb_autopm_get_interface(pegasus->intf);
	if (error)
		return error;

	mutex_lock(&pegasus->pm_mutex);
	pegasus->irq->dev = pegasus->usbdev;
	if (usb_submit_urb(pegasus->irq, GFP_KERNEL)) {
		error = -EIO;
		goto err_autopm_put;
	}

	error = pegasus_set_mode(pegasus, PEN_MODE_XY, NOTETAKER_LED_MOUSE);
	if (error)
		goto err_kill_urb;

	pegasus->is_open = true;
	mutex_unlock(&pegasus->pm_mutex);
	return 0;

err_kill_urb:
	usb_kill_urb(pegasus->irq);
	cancel_work_sync(&pegasus->init);
err_autopm_put:
	mutex_unlock(&pegasus->pm_mutex);
	usb_autopm_put_interface(pegasus->intf);
	return error;
}