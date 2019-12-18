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
struct usbnet {int /*<<< orphan*/  hard_mtu; TYPE_1__* net; scalar_t__ rx_urb_size; } ;
struct usb_interface {int dummy; } ;
struct nc_trailer {int dummy; } ;
struct nc_header {int dummy; } ;
struct TYPE_2__ {scalar_t__ mtu; scalar_t__ hard_header_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NC_MAX_PACKET ; 
 int usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int net1080_bind(struct usbnet *dev, struct usb_interface *intf)
{
	unsigned	extra = sizeof (struct nc_header)
				+ 1
				+ sizeof (struct nc_trailer);

	dev->net->hard_header_len += extra;
	dev->rx_urb_size = dev->net->hard_header_len + dev->net->mtu;
	dev->hard_mtu = NC_MAX_PACKET;
	return usbnet_get_endpoints (dev, intf);
}