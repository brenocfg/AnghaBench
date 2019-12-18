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
struct usbnet {int /*<<< orphan*/  interrupt_mutex; TYPE_1__* udev; scalar_t__ interrupt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

__attribute__((used)) static void __usbnet_status_stop_force(struct usbnet *dev)
{
	if (dev->interrupt) {
		mutex_lock(&dev->interrupt_mutex);
		usb_kill_urb(dev->interrupt);
		dev_dbg(&dev->udev->dev, "killed interrupt URB for suspend\n");
		mutex_unlock(&dev->interrupt_mutex);
	}
}