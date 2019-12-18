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
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 scalar_t__ dvb_usb_device_init (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pctv452e_properties ; 
 int /*<<< orphan*/  tt_connect_s2_3600_properties ; 

__attribute__((used)) static int pctv452e_usb_probe(struct usb_interface *intf,
				const struct usb_device_id *id)
{
	if (0 == dvb_usb_device_init(intf, &pctv452e_properties,
					THIS_MODULE, NULL, adapter_nr) ||
	    0 == dvb_usb_device_init(intf, &tt_connect_s2_3600_properties,
					THIS_MODULE, NULL, adapter_nr))
		return 0;

	return -ENODEV;
}