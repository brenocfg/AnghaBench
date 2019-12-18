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
struct usb_device {int /*<<< orphan*/  devnum; TYPE_1__* bus; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  busnum; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 struct usb_device* to_usb_device (struct device*) ; 

__attribute__((used)) static int usb_dev_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct usb_device *usb_dev;

	usb_dev = to_usb_device(dev);

	if (add_uevent_var(env, "BUSNUM=%03d", usb_dev->bus->busnum))
		return -ENOMEM;

	if (add_uevent_var(env, "DEVNUM=%03d", usb_dev->devnum))
		return -ENOMEM;

	return 0;
}