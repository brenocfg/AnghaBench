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
struct asus_wmi {TYPE_2__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  panel_power; TYPE_1__* quirks; } ;
struct TYPE_3__ {scalar_t__ store_backlight_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_BACKLIGHT ; 
 int FB_BLANK_POWERDOWN ; 
 int FB_BLANK_UNBLANK ; 
 int asus_wmi_get_devstate_simple (struct asus_wmi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_backlight_power(struct asus_wmi *asus)
{
	int ret;

	if (asus->driver->quirks->store_backlight_power)
		ret = !asus->driver->panel_power;
	else
		ret = asus_wmi_get_devstate_simple(asus,
						   ASUS_WMI_DEVID_BACKLIGHT);

	if (ret < 0)
		return ret;

	return ret ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
}