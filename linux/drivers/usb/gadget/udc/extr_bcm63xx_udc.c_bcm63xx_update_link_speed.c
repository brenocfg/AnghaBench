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
typedef  int u32 ;
struct TYPE_2__ {int speed; } ;
struct bcm63xx_udc {TYPE_1__ gadget; int /*<<< orphan*/  dev; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
#define  BCM63XX_SPD_FULL 129 
#define  BCM63XX_SPD_HIGH 128 
 int /*<<< orphan*/  USBD_STATUS_REG ; 
 int USBD_STATUS_SPD_MASK ; 
 int USBD_STATUS_SPD_SHIFT ; 
 int USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int usbd_readl (struct bcm63xx_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm63xx_update_link_speed(struct bcm63xx_udc *udc)
{
	u32 reg = usbd_readl(udc, USBD_STATUS_REG);
	enum usb_device_speed oldspeed = udc->gadget.speed;

	switch ((reg & USBD_STATUS_SPD_MASK) >> USBD_STATUS_SPD_SHIFT) {
	case BCM63XX_SPD_HIGH:
		udc->gadget.speed = USB_SPEED_HIGH;
		break;
	case BCM63XX_SPD_FULL:
		udc->gadget.speed = USB_SPEED_FULL;
		break;
	default:
		/* this should never happen */
		udc->gadget.speed = USB_SPEED_UNKNOWN;
		dev_err(udc->dev,
			"received SETUP packet with invalid link speed\n");
		return 0;
	}

	if (udc->gadget.speed != oldspeed) {
		dev_info(udc->dev, "link up, %s-speed mode\n",
			 udc->gadget.speed == USB_SPEED_HIGH ? "high" : "full");
		return 1;
	} else {
		return 0;
	}
}