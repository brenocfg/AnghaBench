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
struct ina2xx_chip_info {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INA2XX_CONFIG ; 
 int /*<<< orphan*/  INA2XX_MODE_MASK ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ina2xx_chip_info* iio_priv (struct iio_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ina2xx_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct ina2xx_chip_info *chip = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	/* Powerdown */
	return regmap_update_bits(chip->regmap, INA2XX_CONFIG,
				  INA2XX_MODE_MASK, 0);
}