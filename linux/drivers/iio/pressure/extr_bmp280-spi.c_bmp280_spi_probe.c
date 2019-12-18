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
struct spi_device_id {int driver_data; int /*<<< orphan*/  name; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct regmap_config {int dummy; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
#define  BME280_CHIP_ID 130 
#define  BMP180_CHIP_ID 129 
#define  BMP280_CHIP_ID 128 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap_config bmp180_regmap_config ; 
 int bmp280_common_probe (int /*<<< orphan*/ *,struct regmap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bmp280_regmap_bus ; 
 struct regmap_config bmp280_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct regmap* devm_regmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct regmap_config const*) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int bmp280_spi_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);
	struct regmap *regmap;
	const struct regmap_config *regmap_config;
	int ret;

	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "spi_setup failed!\n");
		return ret;
	}

	switch (id->driver_data) {
	case BMP180_CHIP_ID:
		regmap_config = &bmp180_regmap_config;
		break;
	case BMP280_CHIP_ID:
	case BME280_CHIP_ID:
		regmap_config = &bmp280_regmap_config;
		break;
	default:
		return -EINVAL;
	}

	regmap = devm_regmap_init(&spi->dev,
				  &bmp280_regmap_bus,
				  &spi->dev,
				  regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&spi->dev, "failed to allocate register map\n");
		return PTR_ERR(regmap);
	}

	return bmp280_common_probe(&spi->dev,
				   regmap,
				   id->driver_data,
				   id->name,
				   spi->irq);
}