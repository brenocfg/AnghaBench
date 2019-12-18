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
struct TYPE_3__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/ * dev; } ;
struct td028ttec1_panel {TYPE_1__ panel; struct spi_device* spi; int /*<<< orphan*/  backlight; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct td028ttec1_panel* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_of_find_backlight (int /*<<< orphan*/ *) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct td028ttec1_panel*) ; 
 int spi_setup (struct spi_device*) ; 
 int /*<<< orphan*/  td028ttec1_funcs ; 

__attribute__((used)) static int td028ttec1_probe(struct spi_device *spi)
{
	struct td028ttec1_panel *lcd;
	int ret;

	lcd = devm_kzalloc(&spi->dev, sizeof(*lcd), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	spi_set_drvdata(spi, lcd);
	lcd->spi = spi;

	lcd->backlight = devm_of_find_backlight(&spi->dev);
	if (IS_ERR(lcd->backlight))
		return PTR_ERR(lcd->backlight);

	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 9;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "failed to setup SPI: %d\n", ret);
		return ret;
	}

	drm_panel_init(&lcd->panel);
	lcd->panel.dev = &lcd->spi->dev;
	lcd->panel.funcs = &td028ttec1_funcs;

	return drm_panel_add(&lcd->panel);
}