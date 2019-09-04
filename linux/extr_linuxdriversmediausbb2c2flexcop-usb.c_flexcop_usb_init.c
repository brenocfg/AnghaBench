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
struct flexcop_usb {int /*<<< orphan*/  uintf; TYPE_1__* udev; } ;
struct TYPE_2__ {int speed; } ;

/* Variables and functions */
 int ENODEV ; 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_UNKNOWN 128 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  usb_set_interface (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,struct flexcop_usb*) ; 

__attribute__((used)) static int flexcop_usb_init(struct flexcop_usb *fc_usb)
{
	/* use the alternate setting with the larges buffer */
	usb_set_interface(fc_usb->udev,0,1);
	switch (fc_usb->udev->speed) {
	case USB_SPEED_LOW:
		err("cannot handle USB speed because it is too slow.");
		return -ENODEV;
		break;
	case USB_SPEED_FULL:
		info("running at FULL speed.");
		break;
	case USB_SPEED_HIGH:
		info("running at HIGH speed.");
		break;
	case USB_SPEED_UNKNOWN: /* fall through */
	default:
		err("cannot handle USB speed because it is unknown.");
		return -ENODEV;
	}
	usb_set_intfdata(fc_usb->uintf, fc_usb);
	return 0;
}