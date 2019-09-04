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
struct spi_device_id {int /*<<< orphan*/  name; int /*<<< orphan*/  driver_data; } ;
struct spi_device {scalar_t__ max_speed_hz; int /*<<< orphan*/  dev; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ ADXL345_MAX_SPI_FREQ_HZ ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int adxl345_core_probe (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adxl345_spi_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct regmap* devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int adxl345_spi_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);
	struct regmap *regmap;

	/* Bail out if max_speed_hz exceeds 5 MHz */
	if (spi->max_speed_hz > ADXL345_MAX_SPI_FREQ_HZ) {
		dev_err(&spi->dev, "SPI CLK, %d Hz exceeds 5 MHz\n",
			spi->max_speed_hz);
		return -EINVAL;
	}

	regmap = devm_regmap_init_spi(spi, &adxl345_spi_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&spi->dev, "Error initializing spi regmap: %ld\n",
			PTR_ERR(regmap));
		return PTR_ERR(regmap);
	}

	return adxl345_core_probe(&spi->dev, regmap, id->driver_data, id->name);
}