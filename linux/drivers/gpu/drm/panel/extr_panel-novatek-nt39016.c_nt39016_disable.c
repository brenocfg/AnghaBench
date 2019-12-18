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
struct nt39016 {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; int /*<<< orphan*/  backlight; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NT39016_REG_SYSTEM ; 
 int /*<<< orphan*/  NT39016_SYSTEM_RESET_N ; 
 int /*<<< orphan*/  backlight_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nt39016* to_nt39016 (struct drm_panel*) ; 

__attribute__((used)) static int nt39016_disable(struct drm_panel *drm_panel)
{
	struct nt39016 *panel = to_nt39016(drm_panel);
	int err;

	backlight_disable(panel->backlight);

	err = regmap_write(panel->map, NT39016_REG_SYSTEM,
			   NT39016_SYSTEM_RESET_N);
	if (err) {
		dev_err(panel->dev, "Unable to disable panel: %d", err);
		return err;
	}

	return 0;
}