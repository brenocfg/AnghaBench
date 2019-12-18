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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int state; int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct apple_gmux_data {int dummy; } ;

/* Variables and functions */
 int BL_CORE_SUSPENDED ; 
 int /*<<< orphan*/  GMUX_PORT_BRIGHTNESS ; 
 struct apple_gmux_data* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  gmux_write32 (struct apple_gmux_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gmux_update_status(struct backlight_device *bd)
{
	struct apple_gmux_data *gmux_data = bl_get_data(bd);
	u32 brightness = bd->props.brightness;

	if (bd->props.state & BL_CORE_SUSPENDED)
		return 0;

	gmux_write32(gmux_data, GMUX_PORT_BRIGHTNESS, brightness);

	return 0;
}