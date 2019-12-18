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
typedef  int u16 ;
struct usbnet {int /*<<< orphan*/  udev; struct net_device* net; int /*<<< orphan*/  data; } ;
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct net_device {int flags; } ;
struct cdc_state {struct usb_interface* control; } ;
struct TYPE_3__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int USB_CDC_PACKET_TYPE_ALL_MULTICAST ; 
 int USB_CDC_PACKET_TYPE_BROADCAST ; 
 int USB_CDC_PACKET_TYPE_DIRECTED ; 
 int USB_CDC_PACKET_TYPE_PROMISCUOUS ; 
 int /*<<< orphan*/  USB_CDC_SET_ETHERNET_PACKET_FILTER ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  netdev_mc_empty (struct net_device*) ; 
 int /*<<< orphan*/  usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbnet_cdc_update_filter(struct usbnet *dev)
{
	struct cdc_state	*info = (void *) &dev->data;
	struct usb_interface	*intf = info->control;
	struct net_device	*net = dev->net;

	u16 cdc_filter = USB_CDC_PACKET_TYPE_DIRECTED
			| USB_CDC_PACKET_TYPE_BROADCAST;

	/* filtering on the device is an optional feature and not worth
	 * the hassle so we just roughly care about snooping and if any
	 * multicast is requested, we take every multicast
	 */
	if (net->flags & IFF_PROMISC)
		cdc_filter |= USB_CDC_PACKET_TYPE_PROMISCUOUS;
	if (!netdev_mc_empty(net) || (net->flags & IFF_ALLMULTI))
		cdc_filter |= USB_CDC_PACKET_TYPE_ALL_MULTICAST;

	usb_control_msg(dev->udev,
			usb_sndctrlpipe(dev->udev, 0),
			USB_CDC_SET_ETHERNET_PACKET_FILTER,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			cdc_filter,
			intf->cur_altsetting->desc.bInterfaceNumber,
			NULL,
			0,
			USB_CTRL_SET_TIMEOUT
		);
}