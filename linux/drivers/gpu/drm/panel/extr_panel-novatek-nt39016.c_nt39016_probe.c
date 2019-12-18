#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct spi_device {int bits_per_word; int mode; struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct nt39016 {TYPE_1__ drm_panel; int /*<<< orphan*/  backlight; int /*<<< orphan*/  map; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  supply; int /*<<< orphan*/  panel_info; struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_3WIRE ; 
 int SPI_MODE_3 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct nt39016* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_of_find_backlight (struct device*) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  nt39016_funcs ; 
 int /*<<< orphan*/  nt39016_regmap_config ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct nt39016*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int nt39016_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct nt39016 *panel;
	int err;

	panel = devm_kzalloc(dev, sizeof(*panel), GFP_KERNEL);
	if (!panel)
		return -ENOMEM;

	panel->dev = dev;
	spi_set_drvdata(spi, panel);

	panel->panel_info = of_device_get_match_data(dev);
	if (!panel->panel_info)
		return -EINVAL;

	panel->supply = devm_regulator_get(dev, "power");
	if (IS_ERR(panel->supply)) {
		dev_err(dev, "Failed to get power supply");
		return PTR_ERR(panel->supply);
	}

	panel->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(panel->reset_gpio)) {
		dev_err(dev, "Failed to get reset GPIO");
		return PTR_ERR(panel->reset_gpio);
	}

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_3 | SPI_3WIRE;
	err = spi_setup(spi);
	if (err) {
		dev_err(dev, "Failed to setup SPI");
		return err;
	}

	panel->map = devm_regmap_init_spi(spi, &nt39016_regmap_config);
	if (IS_ERR(panel->map)) {
		dev_err(dev, "Failed to init regmap");
		return PTR_ERR(panel->map);
	}

	panel->backlight = devm_of_find_backlight(dev);
	if (IS_ERR(panel->backlight)) {
		err = PTR_ERR(panel->backlight);
		if (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get backlight handle");
		return err;
	}

	drm_panel_init(&panel->drm_panel);
	panel->drm_panel.dev = dev;
	panel->drm_panel.funcs = &nt39016_funcs;

	err = drm_panel_add(&panel->drm_panel);
	if (err < 0) {
		dev_err(dev, "Failed to register panel");
		return err;
	}

	return 0;
}