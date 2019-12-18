#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  speed; TYPE_1__* ep0; } ;
struct renesas_usb3 {TYPE_2__ gadget; } ;
struct TYPE_3__ {void* maxpacket; } ;

/* Variables and functions */
 void* USB3_EP0_HSFS_MAX_PACKET_SIZE ; 
 void* USB3_EP0_SS_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  USB3_USB_STA ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
#define  USB_STA_SPEED_FS 130 
#define  USB_STA_SPEED_HS 129 
 int USB_STA_SPEED_MASK ; 
#define  USB_STA_SPEED_SS 128 
 int usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_irq_epc_int_1_speed(struct renesas_usb3 *usb3)
{
	u32 speed = usb3_read(usb3, USB3_USB_STA) & USB_STA_SPEED_MASK;

	switch (speed) {
	case USB_STA_SPEED_SS:
		usb3->gadget.speed = USB_SPEED_SUPER;
		usb3->gadget.ep0->maxpacket = USB3_EP0_SS_MAX_PACKET_SIZE;
		break;
	case USB_STA_SPEED_HS:
		usb3->gadget.speed = USB_SPEED_HIGH;
		usb3->gadget.ep0->maxpacket = USB3_EP0_HSFS_MAX_PACKET_SIZE;
		break;
	case USB_STA_SPEED_FS:
		usb3->gadget.speed = USB_SPEED_FULL;
		usb3->gadget.ep0->maxpacket = USB3_EP0_HSFS_MAX_PACKET_SIZE;
		break;
	default:
		usb3->gadget.speed = USB_SPEED_UNKNOWN;
		break;
	}
}