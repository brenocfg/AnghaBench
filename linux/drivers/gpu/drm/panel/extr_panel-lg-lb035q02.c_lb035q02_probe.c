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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/ * dev; } ;
struct lb035q02_device {TYPE_1__ panel; struct spi_device* spi; int /*<<< orphan*/  enable_gpio; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct lb035q02_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  lb035q02_funcs ; 
 int lb035q02_init (struct lb035q02_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct lb035q02_device*) ; 

__attribute__((used)) static int lb035q02_probe(struct spi_device *spi)
{
	struct lb035q02_device *lcd;
	int ret;

	lcd = devm_kzalloc(&spi->dev, sizeof(*lcd), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	spi_set_drvdata(spi, lcd);
	lcd->spi = spi;

	lcd->enable_gpio = devm_gpiod_get(&spi->dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(lcd->enable_gpio)) {
		dev_err(&spi->dev, "failed to parse enable gpio\n");
		return PTR_ERR(lcd->enable_gpio);
	}

	ret = lb035q02_init(lcd);
	if (ret < 0)
		return ret;

	drm_panel_init(&lcd->panel);
	lcd->panel.dev = &lcd->spi->dev;
	lcd->panel.funcs = &lb035q02_funcs;

	return drm_panel_add(&lcd->panel);
}