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
struct backlight_properties {int brightness; } ;
struct backlight_device {struct backlight_properties props; } ;

/* Variables and functions */

__attribute__((used)) static int tosa_bl_get_brightness(struct backlight_device *dev)
{
	struct backlight_properties *props = &dev->props;

	return props->brightness;
}