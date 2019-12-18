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
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int USB_SPEED_UNKNOWN ; 
 int device_property_read_string (struct device*,char*,char const**) ; 
 int match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  speed_names ; 

enum usb_device_speed usb_get_maximum_speed(struct device *dev)
{
	const char *maximum_speed;
	int ret;

	ret = device_property_read_string(dev, "maximum-speed", &maximum_speed);
	if (ret < 0)
		return USB_SPEED_UNKNOWN;

	ret = match_string(speed_names, ARRAY_SIZE(speed_names), maximum_speed);

	return (ret < 0) ? USB_SPEED_UNKNOWN : ret;
}