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
typedef  int uint8_t ;
struct regulator_dev {int dummy; } ;
struct device {int dummy; } ;
struct da903x_regulator_info {unsigned int vol_shift; int vol_nbits; int update_bit; int /*<<< orphan*/  update_reg; int /*<<< orphan*/  vol_reg; } ;

/* Variables and functions */
 int da903x_set_bits (struct device*,int /*<<< orphan*/ ,int) ; 
 int da903x_update (struct device*,int /*<<< orphan*/ ,int,int) ; 
 struct da903x_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 struct device* to_da903x_dev (struct regulator_dev*) ; 

__attribute__((used)) static int da9034_set_dvc_voltage_sel(struct regulator_dev *rdev,
				      unsigned selector)
{
	struct da903x_regulator_info *info = rdev_get_drvdata(rdev);
	struct device *da9034_dev = to_da903x_dev(rdev);
	uint8_t val, mask;
	int ret;

	val = selector << info->vol_shift;
	mask = ((1 << info->vol_nbits) - 1)  << info->vol_shift;

	ret = da903x_update(da9034_dev, info->vol_reg, val, mask);
	if (ret)
		return ret;

	ret = da903x_set_bits(da9034_dev, info->update_reg,
					1 << info->update_bit);
	return ret;
}