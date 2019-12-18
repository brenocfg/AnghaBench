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
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ brightness; scalar_t__ max_brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct asus_wmi {TYPE_2__* driver; } ;
struct TYPE_4__ {scalar_t__ brightness; } ;

/* Variables and functions */
 struct asus_wmi* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static u32 get_scalar_command(struct backlight_device *bd)
{
	struct asus_wmi *asus = bl_get_data(bd);
	u32 ctrl_param = 0;

	if ((asus->driver->brightness < bd->props.brightness) ||
	    bd->props.brightness == bd->props.max_brightness)
		ctrl_param = 0x00008001;
	else if ((asus->driver->brightness > bd->props.brightness) ||
		 bd->props.brightness == 0)
		ctrl_param = 0x00008000;

	asus->driver->brightness = bd->props.brightness;

	return ctrl_param;
}