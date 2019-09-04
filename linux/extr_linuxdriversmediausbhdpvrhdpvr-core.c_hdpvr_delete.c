#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hdpvr_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdpvr_free_buffers (struct hdpvr_device*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

void hdpvr_delete(struct hdpvr_device *dev)
{
	hdpvr_free_buffers(dev);
	usb_put_dev(dev->udev);
}