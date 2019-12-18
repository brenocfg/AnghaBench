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
struct usb3503 {struct device* dev; } ;
struct device {int dummy; } ;
typedef  enum usb3503_mode { ____Placeholder_usb3503_mode } usb3503_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  USB3503_MODE_HUB 129 
#define  USB3503_MODE_STANDBY 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int usb3503_connect (struct usb3503*) ; 
 int /*<<< orphan*/  usb3503_reset (struct usb3503*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb3503_switch_mode(struct usb3503 *hub, enum usb3503_mode mode)
{
	struct device *dev = hub->dev;
	int err = 0;

	switch (mode) {
	case USB3503_MODE_HUB:
		err = usb3503_connect(hub);
		break;

	case USB3503_MODE_STANDBY:
		usb3503_reset(hub, 0);
		dev_info(dev, "switched to STANDBY mode\n");
		break;

	default:
		dev_err(dev, "unknown mode is requested\n");
		err = -EINVAL;
		break;
	}

	return err;
}