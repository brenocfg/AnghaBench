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
struct usb_hub {int /*<<< orphan*/  power_bits; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_PORT_FEAT_POWER ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int set_port_feature (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int usb_clear_port_feature (struct usb_device*,int,int /*<<< orphan*/ ) ; 

int usb_hub_set_port_power(struct usb_device *hdev, struct usb_hub *hub,
			   int port1, bool set)
{
	int ret;

	if (set)
		ret = set_port_feature(hdev, port1, USB_PORT_FEAT_POWER);
	else
		ret = usb_clear_port_feature(hdev, port1, USB_PORT_FEAT_POWER);

	if (ret)
		return ret;

	if (set)
		set_bit(port1, hub->power_bits);
	else
		clear_bit(port1, hub->power_bits);
	return 0;
}