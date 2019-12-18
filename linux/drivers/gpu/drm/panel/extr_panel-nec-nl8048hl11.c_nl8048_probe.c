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
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/ * dev; } ;
struct nl8048_panel {TYPE_1__ panel; struct spi_device* spi; int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct nl8048_panel* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  nl8048_funcs ; 
 int nl8048_init (struct nl8048_panel*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct nl8048_panel*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int nl8048_probe(struct spi_device *spi)
{
	struct nl8048_panel *lcd;
	int ret;

	lcd = devm_kzalloc(&spi->dev, sizeof(*lcd), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	spi_set_drvdata(spi, lcd);
	lcd->spi = spi;

	lcd->reset_gpio = devm_gpiod_get(&spi->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(lcd->reset_gpio)) {
		dev_err(&spi->dev, "failed to parse reset gpio\n");
		return PTR_ERR(lcd->reset_gpio);
	}

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 32;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "failed to setup SPI: %d\n", ret);
		return ret;
	}

	ret = nl8048_init(lcd);
	if (ret < 0)
		return ret;

	drm_panel_init(&lcd->panel);
	lcd->panel.dev = &lcd->spi->dev;
	lcd->panel.funcs = &nl8048_funcs;

	return drm_panel_add(&lcd->panel);
}