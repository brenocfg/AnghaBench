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
struct usbnet {TYPE_1__* net; scalar_t__ hard_mtu; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {scalar_t__ hard_header_len; scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ EEM_HEAD ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ VLAN_HLEN ; 
 int usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int eem_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int status = 0;

	status = usbnet_get_endpoints(dev, intf);
	if (status < 0)
		return status;

	/* no jumbogram (16K) support for now */

	dev->net->hard_header_len += EEM_HEAD + ETH_FCS_LEN + VLAN_HLEN;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;

	return 0;
}