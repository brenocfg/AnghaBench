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
struct fxas21002c_data {unsigned int chip_id; int /*<<< orphan*/ * regmap_fields; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int FXAS21002C_CHIP_ID_1 ; 
 unsigned int FXAS21002C_CHIP_ID_2 ; 
 int /*<<< orphan*/  FXAS21002C_MODE_STANDBY ; 
 size_t F_WHO_AM_I ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int fxas21002c_mode_set (struct fxas21002c_data*,int /*<<< orphan*/ ) ; 
 int fxas21002c_odr_set (struct fxas21002c_data*,int) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fxas21002c_chip_init(struct fxas21002c_data *data)
{
	struct device *dev = regmap_get_device(data->regmap);
	unsigned int chip_id;
	int ret;

	ret = regmap_field_read(data->regmap_fields[F_WHO_AM_I], &chip_id);
	if (ret < 0)
		return ret;

	if (chip_id != FXAS21002C_CHIP_ID_1 &&
	    chip_id != FXAS21002C_CHIP_ID_2) {
		dev_err(dev, "chip id 0x%02x is not supported\n", chip_id);
		return -EINVAL;
	}

	data->chip_id = chip_id;

	ret = fxas21002c_mode_set(data, FXAS21002C_MODE_STANDBY);
	if (ret < 0)
		return ret;

	/* Set ODR to 200HZ as default */
	ret = fxas21002c_odr_set(data, 200);
	if (ret < 0)
		dev_err(dev, "failed to set ODR: %d\n", ret);

	return ret;
}