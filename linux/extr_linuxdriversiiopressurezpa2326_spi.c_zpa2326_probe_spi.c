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
struct spi_device {int bits_per_word; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  mode; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  ZPA2326_DEVICE_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct regmap* devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* spi_get_device_id (struct spi_device*) ; 
 int spi_setup (struct spi_device*) ; 
 int zpa2326_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regmap*) ; 
 int /*<<< orphan*/  zpa2326_regmap_spi_config ; 

__attribute__((used)) static int zpa2326_probe_spi(struct spi_device *spi)
{
	struct regmap *regmap;
	int            err;

	regmap = devm_regmap_init_spi(spi, &zpa2326_regmap_spi_config);
	if (IS_ERR(regmap)) {
		dev_err(&spi->dev, "failed to init registers map");
		return PTR_ERR(regmap);
	}

	/*
	 * Enforce SPI slave settings to prevent from DT misconfiguration.
	 *
	 * Clock is idle high. Sampling happens on trailing edge, i.e., rising
	 * edge. Maximum bus frequency is 1 MHz. Registers are 8 bits wide.
	 */
	spi->mode = SPI_MODE_3;
	spi->max_speed_hz = min(spi->max_speed_hz, 1000000U);
	spi->bits_per_word = 8;
	err = spi_setup(spi);
	if (err < 0)
		return err;

	return zpa2326_probe(&spi->dev, spi_get_device_id(spi)->name,
			     spi->irq, ZPA2326_DEVICE_ID, regmap);
}