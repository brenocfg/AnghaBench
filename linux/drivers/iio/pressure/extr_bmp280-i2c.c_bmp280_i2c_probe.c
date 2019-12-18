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
struct regmap_config {int dummy; } ;
struct regmap {int dummy; } ;
struct i2c_device_id {int /*<<< orphan*/  name; int /*<<< orphan*/  driver_data; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  BME280_CHIP_ID 130 
#define  BMP180_CHIP_ID 129 
#define  BMP280_CHIP_ID 128 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap_config bmp180_regmap_config ; 
 int bmp280_common_probe (int /*<<< orphan*/ *,struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regmap_config bmp280_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 

__attribute__((used)) static int bmp280_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct regmap *regmap;
	const struct regmap_config *regmap_config;

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

	regmap = devm_regmap_init_i2c(client, regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "failed to allocate register map\n");
		return PTR_ERR(regmap);
	}

	return bmp280_common_probe(&client->dev,
				   regmap,
				   id->driver_data,
				   id->name,
				   client->irq);
}