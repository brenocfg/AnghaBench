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
struct nt39016 {int /*<<< orphan*/  supply; int /*<<< orphan*/  dev; int /*<<< orphan*/  map; int /*<<< orphan*/  reset_gpio; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nt39016_panel_regs ; 
 int regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct nt39016* to_nt39016 (struct drm_panel*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int nt39016_prepare(struct drm_panel *drm_panel)
{
	struct nt39016 *panel = to_nt39016(drm_panel);
	int err;

	err = regulator_enable(panel->supply);
	if (err) {
		dev_err(panel->dev, "Failed to enable power supply: %d", err);
		return err;
	}

	/*
	 * Reset the NT39016.
	 * The documentation says the reset pulse should be at least 40 us to
	 * pass the glitch filter, but when testing I see some resets fail and
	 * some succeed when using a 70 us delay, so we use 100 us instead.
	 */
	gpiod_set_value_cansleep(panel->reset_gpio, 1);
	usleep_range(100, 1000);
	gpiod_set_value_cansleep(panel->reset_gpio, 0);
	udelay(2);

	/* Init all registers. */
	err = regmap_multi_reg_write(panel->map, nt39016_panel_regs,
				     ARRAY_SIZE(nt39016_panel_regs));
	if (err) {
		dev_err(panel->dev, "Failed to init registers: %d", err);
		goto err_disable_regulator;
	}

	return 0;

err_disable_regulator:
	regulator_disable(panel->supply);
	return err;
}