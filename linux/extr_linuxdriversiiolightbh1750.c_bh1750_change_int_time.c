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
typedef  int u16 ;
struct bh1750_data {int mtreg; int /*<<< orphan*/  client; struct bh1750_chip_info* chip_info; } ;
struct bh1750_chip_info {int mtreg_to_usec; int mtreg_min; int mtreg_max; int int_time_high_mask; int int_time_low_mask; } ;

/* Variables and functions */
 int BH1750_CHANGE_INT_TIME_H_BIT ; 
 int BH1750_CHANGE_INT_TIME_L_BIT ; 
 int BH1750_POWER_DOWN ; 
 int EINVAL ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bh1750_change_int_time(struct bh1750_data *data, int usec)
{
	int ret;
	u16 val;
	u8 regval;
	const struct bh1750_chip_info *chip_info = data->chip_info;

	if ((usec % chip_info->mtreg_to_usec) != 0)
		return -EINVAL;

	val = usec / chip_info->mtreg_to_usec;
	if (val < chip_info->mtreg_min || val > chip_info->mtreg_max)
		return -EINVAL;

	ret = i2c_smbus_write_byte(data->client, BH1750_POWER_DOWN);
	if (ret < 0)
		return ret;

	regval = (val & chip_info->int_time_high_mask) >> 5;
	ret = i2c_smbus_write_byte(data->client,
				   BH1750_CHANGE_INT_TIME_H_BIT | regval);
	if (ret < 0)
		return ret;

	regval = val & chip_info->int_time_low_mask;
	ret = i2c_smbus_write_byte(data->client,
				   BH1750_CHANGE_INT_TIME_L_BIT | regval);
	if (ret < 0)
		return ret;

	data->mtreg = val;

	return 0;
}