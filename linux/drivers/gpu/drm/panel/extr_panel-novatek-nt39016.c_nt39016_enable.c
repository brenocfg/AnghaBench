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
struct nt39016 {scalar_t__ backlight; int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NT39016_REG_SYSTEM ; 
 int NT39016_SYSTEM_RESET_N ; 
 int NT39016_SYSTEM_STANDBY ; 
 int backlight_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nt39016* to_nt39016 (struct drm_panel*) ; 

__attribute__((used)) static int nt39016_enable(struct drm_panel *drm_panel)
{
	struct nt39016 *panel = to_nt39016(drm_panel);
	int ret;

	ret = regmap_write(panel->map, NT39016_REG_SYSTEM,
			   NT39016_SYSTEM_RESET_N | NT39016_SYSTEM_STANDBY);
	if (ret) {
		dev_err(panel->dev, "Unable to enable panel: %d", ret);
		return ret;
	}

	if (panel->backlight) {
		/* Wait for the picture to be ready before enabling backlight */
		msleep(150);

		ret = backlight_enable(panel->backlight);
	}

	return ret;
}