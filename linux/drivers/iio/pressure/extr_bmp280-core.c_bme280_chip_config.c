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
typedef  int /*<<< orphan*/  u8 ;
struct bmp280_data {int /*<<< orphan*/  regmap; scalar_t__ oversampling_humid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMP280_OSRS_HUMIDITIY_X (scalar_t__) ; 
 int /*<<< orphan*/  BMP280_OSRS_HUMIDITY_MASK ; 
 int /*<<< orphan*/  BMP280_REG_CTRL_HUMIDITY ; 
 int bmp280_chip_config (struct bmp280_data*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bme280_chip_config(struct bmp280_data *data)
{
	int ret;
	u8 osrs = BMP280_OSRS_HUMIDITIY_X(data->oversampling_humid + 1);

	/*
	 * Oversampling of humidity must be set before oversampling of
	 * temperature/pressure is set to become effective.
	 */
	ret = regmap_update_bits(data->regmap, BMP280_REG_CTRL_HUMIDITY,
				  BMP280_OSRS_HUMIDITY_MASK, osrs);

	if (ret < 0)
		return ret;

	return bmp280_chip_config(data);
}