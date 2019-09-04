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
struct tegra_sor {int /*<<< orphan*/  scdc; int /*<<< orphan*/  dev; void* hdmi_supply; void* vdd_pll_supply; void* avdd_io_supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* devm_regulator_get (int /*<<< orphan*/ ,char*) ; 
 int regulator_enable (void*) ; 
 int /*<<< orphan*/  tegra_sor_hdmi_scdc_work ; 

__attribute__((used)) static int tegra_sor_hdmi_probe(struct tegra_sor *sor)
{
	int err;

	sor->avdd_io_supply = devm_regulator_get(sor->dev, "avdd-io");
	if (IS_ERR(sor->avdd_io_supply)) {
		dev_err(sor->dev, "cannot get AVDD I/O supply: %ld\n",
			PTR_ERR(sor->avdd_io_supply));
		return PTR_ERR(sor->avdd_io_supply);
	}

	err = regulator_enable(sor->avdd_io_supply);
	if (err < 0) {
		dev_err(sor->dev, "failed to enable AVDD I/O supply: %d\n",
			err);
		return err;
	}

	sor->vdd_pll_supply = devm_regulator_get(sor->dev, "vdd-pll");
	if (IS_ERR(sor->vdd_pll_supply)) {
		dev_err(sor->dev, "cannot get VDD PLL supply: %ld\n",
			PTR_ERR(sor->vdd_pll_supply));
		return PTR_ERR(sor->vdd_pll_supply);
	}

	err = regulator_enable(sor->vdd_pll_supply);
	if (err < 0) {
		dev_err(sor->dev, "failed to enable VDD PLL supply: %d\n",
			err);
		return err;
	}

	sor->hdmi_supply = devm_regulator_get(sor->dev, "hdmi");
	if (IS_ERR(sor->hdmi_supply)) {
		dev_err(sor->dev, "cannot get HDMI supply: %ld\n",
			PTR_ERR(sor->hdmi_supply));
		return PTR_ERR(sor->hdmi_supply);
	}

	err = regulator_enable(sor->hdmi_supply);
	if (err < 0) {
		dev_err(sor->dev, "failed to enable HDMI supply: %d\n", err);
		return err;
	}

	INIT_DELAYED_WORK(&sor->scdc, tegra_sor_hdmi_scdc_work);

	return 0;
}