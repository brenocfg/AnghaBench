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
struct backlight_device {int dummy; } ;
struct apple_gmux_data {int dummy; } ;

/* Variables and functions */
 int GMUX_BRIGHTNESS_MASK ; 
 int /*<<< orphan*/  GMUX_PORT_BRIGHTNESS ; 
 struct apple_gmux_data* bl_get_data (struct backlight_device*) ; 
 int gmux_read32 (struct apple_gmux_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gmux_get_brightness(struct backlight_device *bd)
{
	struct apple_gmux_data *gmux_data = bl_get_data(bd);
	return gmux_read32(gmux_data, GMUX_PORT_BRIGHTNESS) &
	       GMUX_BRIGHTNESS_MASK;
}