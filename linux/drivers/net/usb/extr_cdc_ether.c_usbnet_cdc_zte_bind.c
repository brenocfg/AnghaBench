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
struct usbnet {TYPE_1__* net; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_1__*) ; 
 int usbnet_cdc_bind (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int usbnet_cdc_zte_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int status = usbnet_cdc_bind(dev, intf);

	if (!status && (dev->net->dev_addr[0] & 0x02))
		eth_hw_addr_random(dev->net);

	return status;
}