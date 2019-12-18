#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {int hard_mtu; int rx_urb_size; TYPE_2__* net; int /*<<< orphan*/ * status; int /*<<< orphan*/  udev; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct usb_interface {TYPE_1__* cur_altsetting; } ;
struct TYPE_6__ {scalar_t__ bInterfaceClass; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  hard_header_len; } ;
struct TYPE_4__ {TYPE_3__ desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 scalar_t__ KALMIA_HEADER_LENGTH ; 
 scalar_t__ USB_CLASS_VENDOR_SPEC ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int kalmia_init_and_get_ethernet_addr (struct usbnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
kalmia_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int status;
	u8 ethernet_addr[ETH_ALEN];

	/* Don't bind to AT command interface */
	if (intf->cur_altsetting->desc.bInterfaceClass != USB_CLASS_VENDOR_SPEC)
		return -EINVAL;

	dev->in = usb_rcvbulkpipe(dev->udev, 0x81 & USB_ENDPOINT_NUMBER_MASK);
	dev->out = usb_sndbulkpipe(dev->udev, 0x02 & USB_ENDPOINT_NUMBER_MASK);
	dev->status = NULL;

	dev->net->hard_header_len += KALMIA_HEADER_LENGTH;
	dev->hard_mtu = 1400;
	dev->rx_urb_size = dev->hard_mtu * 10; // Found as optimal after testing

	status = kalmia_init_and_get_ethernet_addr(dev, ethernet_addr);
	if (status)
		return status;

	memcpy(dev->net->dev_addr, ethernet_addr, ETH_ALEN);

	return status;
}