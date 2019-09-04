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
typedef  int u8 ;
struct bmp280_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; scalar_t__ oversampling_press; scalar_t__ oversampling_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMP280_FILTER_4X ; 
 int /*<<< orphan*/  BMP280_FILTER_MASK ; 
 int BMP280_MODE_MASK ; 
 int BMP280_MODE_NORMAL ; 
 int BMP280_OSRS_PRESS_MASK ; 
 int BMP280_OSRS_PRESS_X (scalar_t__) ; 
 int BMP280_OSRS_TEMP_MASK ; 
 int BMP280_OSRS_TEMP_X (scalar_t__) ; 
 int /*<<< orphan*/  BMP280_REG_CONFIG ; 
 int /*<<< orphan*/  BMP280_REG_CTRL_MEAS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int bmp280_chip_config(struct bmp280_data *data)
{
	int ret;
	u8 osrs = BMP280_OSRS_TEMP_X(data->oversampling_temp + 1) |
		  BMP280_OSRS_PRESS_X(data->oversampling_press + 1);

	ret = regmap_write_bits(data->regmap, BMP280_REG_CTRL_MEAS,
				 BMP280_OSRS_TEMP_MASK |
				 BMP280_OSRS_PRESS_MASK |
				 BMP280_MODE_MASK,
				 osrs | BMP280_MODE_NORMAL);
	if (ret < 0) {
		dev_err(data->dev,
			"failed to write ctrl_meas register\n");
		return ret;
	}

	ret = regmap_update_bits(data->regmap, BMP280_REG_CONFIG,
				 BMP280_FILTER_MASK,
				 BMP280_FILTER_4X);
	if (ret < 0) {
		dev_err(data->dev,
			"failed to write config register\n");
		return ret;
	}

	return ret;
}