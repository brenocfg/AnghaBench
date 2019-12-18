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
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/ * dev; } ;
struct acx565akm_panel {scalar_t__ has_bc; TYPE_1__ panel; struct spi_device* spi; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  acx565akm_backlight_cleanup (struct acx565akm_panel*) ; 
 int acx565akm_backlight_init (struct acx565akm_panel*) ; 
 int acx565akm_detect (struct acx565akm_panel*) ; 
 int /*<<< orphan*/  acx565akm_funcs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct acx565akm_panel* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct acx565akm_panel*) ; 

__attribute__((used)) static int acx565akm_probe(struct spi_device *spi)
{
	struct acx565akm_panel *lcd;
	int ret;

	lcd = devm_kzalloc(&spi->dev, sizeof(*lcd), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	spi_set_drvdata(spi, lcd);
	spi->mode = SPI_MODE_3;

	lcd->spi = spi;
	mutex_init(&lcd->mutex);

	lcd->reset_gpio = devm_gpiod_get(&spi->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(lcd->reset_gpio)) {
		dev_err(&spi->dev, "failed to get reset GPIO\n");
		return PTR_ERR(lcd->reset_gpio);
	}

	ret = acx565akm_detect(lcd);
	if (ret < 0) {
		dev_err(&spi->dev, "panel detection failed\n");
		return ret;
	}

	if (lcd->has_bc) {
		ret = acx565akm_backlight_init(lcd);
		if (ret < 0)
			return ret;
	}

	drm_panel_init(&lcd->panel);
	lcd->panel.dev = &lcd->spi->dev;
	lcd->panel.funcs = &acx565akm_funcs;

	ret = drm_panel_add(&lcd->panel);
	if (ret < 0) {
		if (lcd->has_bc)
			acx565akm_backlight_cleanup(lcd);
		return ret;
	}

	return 0;
}