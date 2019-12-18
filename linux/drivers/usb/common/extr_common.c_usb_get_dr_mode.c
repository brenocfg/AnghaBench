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
struct device {int dummy; } ;
typedef  enum usb_dr_mode { ____Placeholder_usb_dr_mode } usb_dr_mode ;

/* Variables and functions */
 int USB_DR_MODE_UNKNOWN ; 
 int device_property_read_string (struct device*,char*,char const**) ; 
 int usb_get_dr_mode_from_string (char const*) ; 

enum usb_dr_mode usb_get_dr_mode(struct device *dev)
{
	const char *dr_mode;
	int err;

	err = device_property_read_string(dev, "dr_mode", &dr_mode);
	if (err < 0)
		return USB_DR_MODE_UNKNOWN;

	return usb_get_dr_mode_from_string(dr_mode);
}