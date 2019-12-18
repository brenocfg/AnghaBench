#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * funcs; TYPE_3__* dev; } ;
struct td043mtea1_panel {TYPE_1__ panel; struct spi_device* spi; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  vcc_reg; int /*<<< orphan*/  gamma; int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct spi_device {int bits_per_word; TYPE_3__ dev; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  TPO_R02_MODE_800x480 ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 struct td043mtea1_panel* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_3__*,char*) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct td043mtea1_panel*) ; 
 int spi_setup (struct spi_device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  td043mtea1_attr_group ; 
 int /*<<< orphan*/  td043mtea1_def_gamma ; 
 int /*<<< orphan*/  td043mtea1_funcs ; 

__attribute__((used)) static int td043mtea1_probe(struct spi_device *spi)
{
	struct td043mtea1_panel *lcd;
	int ret;

	lcd = devm_kzalloc(&spi->dev, sizeof(*lcd), GFP_KERNEL);
	if (lcd == NULL)
		return -ENOMEM;

	spi_set_drvdata(spi, lcd);
	lcd->spi = spi;
	lcd->mode = TPO_R02_MODE_800x480;
	memcpy(lcd->gamma, td043mtea1_def_gamma, sizeof(lcd->gamma));

	lcd->vcc_reg = devm_regulator_get(&spi->dev, "vcc");
	if (IS_ERR(lcd->vcc_reg)) {
		dev_err(&spi->dev, "failed to get VCC regulator\n");
		return PTR_ERR(lcd->vcc_reg);
	}

	lcd->reset_gpio = devm_gpiod_get(&spi->dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(lcd->reset_gpio)) {
		dev_err(&spi->dev, "failed to get reset GPIO\n");
		return PTR_ERR(lcd->reset_gpio);
	}

	spi->bits_per_word = 16;
	spi->mode = SPI_MODE_0;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "failed to setup SPI: %d\n", ret);
		return ret;
	}

	ret = sysfs_create_group(&spi->dev.kobj, &td043mtea1_attr_group);
	if (ret < 0) {
		dev_err(&spi->dev, "failed to create sysfs files\n");
		return ret;
	}

	drm_panel_init(&lcd->panel);
	lcd->panel.dev = &lcd->spi->dev;
	lcd->panel.funcs = &td043mtea1_funcs;

	ret = drm_panel_add(&lcd->panel);
	if (ret < 0) {
		sysfs_remove_group(&spi->dev.kobj, &td043mtea1_attr_group);
		return ret;
	}

	return 0;
}