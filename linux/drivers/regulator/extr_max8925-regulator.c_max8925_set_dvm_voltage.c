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
struct regulator_dev {int dummy; } ;
struct max8925_regulator_info {int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 unsigned char DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned char SD1_DVM_SHIFT ; 
 int /*<<< orphan*/  SD1_DVM_STEP ; 
 int SD1_DVM_VMAX ; 
 int SD1_DVM_VMIN ; 
 int max8925_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,unsigned char) ; 
 struct max8925_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int max8925_set_dvm_voltage(struct regulator_dev *rdev, int uV)
{
	struct max8925_regulator_info *info = rdev_get_drvdata(rdev);
	unsigned char data, mask;

	if (uV < SD1_DVM_VMIN || uV > SD1_DVM_VMAX)
		return -EINVAL;

	data = DIV_ROUND_UP(uV - SD1_DVM_VMIN, SD1_DVM_STEP);
	data <<= SD1_DVM_SHIFT;
	mask = 3 << SD1_DVM_SHIFT;

	return max8925_set_bits(info->i2c, info->enable_reg, mask, data);
}