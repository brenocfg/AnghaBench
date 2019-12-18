#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; } ;
struct lms501kf03 {int /*<<< orphan*/  power; TYPE_1__* lcd_pd; struct lcd_device* ld; int /*<<< orphan*/ * dev; struct spi_device* spi; } ;
struct lcd_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lcd_enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 int PTR_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct lms501kf03* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct lcd_device* devm_lcd_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct lms501kf03*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lms501kf03_lcd_ops ; 
 int /*<<< orphan*/  lms501kf03_power (struct lms501kf03*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct lms501kf03*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int lms501kf03_probe(struct spi_device *spi)
{
	struct lms501kf03 *lcd = NULL;
	struct lcd_device *ld = NULL;
	int ret = 0;

	lcd = devm_kzalloc(&spi->dev, sizeof(struct lms501kf03), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	/* lms501kf03 lcd panel uses 3-wire 9-bit SPI Mode. */
	spi->bits_per_word = 9;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "spi setup failed.\n");
		return ret;
	}

	lcd->spi = spi;
	lcd->dev = &spi->dev;

	lcd->lcd_pd = dev_get_platdata(&spi->dev);
	if (!lcd->lcd_pd) {
		dev_err(&spi->dev, "platform data is NULL\n");
		return -EINVAL;
	}

	ld = devm_lcd_device_register(&spi->dev, "lms501kf03", &spi->dev, lcd,
					&lms501kf03_lcd_ops);
	if (IS_ERR(ld))
		return PTR_ERR(ld);

	lcd->ld = ld;

	if (!lcd->lcd_pd->lcd_enabled) {
		/*
		 * if lcd panel was off from bootloader then
		 * current lcd status is powerdown and then
		 * it enables lcd panel.
		 */
		lcd->power = FB_BLANK_POWERDOWN;

		lms501kf03_power(lcd, FB_BLANK_UNBLANK);
	} else {
		lcd->power = FB_BLANK_UNBLANK;
	}

	spi_set_drvdata(spi, lcd);

	dev_info(&spi->dev, "lms501kf03 panel driver has been probed.\n");

	return 0;
}