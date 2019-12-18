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
struct usb_qualifier_descriptor {int bLength; int bNumConfigurations; scalar_t__ bRESERVED; int /*<<< orphan*/  bMaxPacketSize0; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  bcdUSB; int /*<<< orphan*/  bDescriptorType; } ;
struct usb_device_descriptor {int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; } ;
struct dev_data {int /*<<< orphan*/  rbuf; TYPE_2__* gadget; struct usb_device_descriptor* dev; } ;
struct TYPE_4__ {TYPE_1__* ep0; } ;
struct TYPE_3__ {int /*<<< orphan*/  maxpacket; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DT_DEVICE_QUALIFIER ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct usb_qualifier_descriptor*,int) ; 

__attribute__((used)) static void make_qualifier (struct dev_data *dev)
{
	struct usb_qualifier_descriptor		qual;
	struct usb_device_descriptor		*desc;

	qual.bLength = sizeof qual;
	qual.bDescriptorType = USB_DT_DEVICE_QUALIFIER;
	qual.bcdUSB = cpu_to_le16 (0x0200);

	desc = dev->dev;
	qual.bDeviceClass = desc->bDeviceClass;
	qual.bDeviceSubClass = desc->bDeviceSubClass;
	qual.bDeviceProtocol = desc->bDeviceProtocol;

	/* assumes ep0 uses the same value for both speeds ... */
	qual.bMaxPacketSize0 = dev->gadget->ep0->maxpacket;

	qual.bNumConfigurations = 1;
	qual.bRESERVED = 0;

	memcpy (dev->rbuf, &qual, sizeof qual);
}