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
struct device_node {int dummy; } ;
typedef  enum usb_phy_interface { ____Placeholder_usb_phy_interface } usb_phy_interface ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int USBPHY_INTERFACE_MODE_UNKNOWN ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * usbphy_modes ; 

enum usb_phy_interface of_usb_get_phy_mode(struct device_node *np)
{
	const char *phy_type;
	int err, i;

	err = of_property_read_string(np, "phy_type", &phy_type);
	if (err < 0)
		return USBPHY_INTERFACE_MODE_UNKNOWN;

	for (i = 0; i < ARRAY_SIZE(usbphy_modes); i++)
		if (!strcmp(phy_type, usbphy_modes[i]))
			return i;

	return USBPHY_INTERFACE_MODE_UNKNOWN;
}