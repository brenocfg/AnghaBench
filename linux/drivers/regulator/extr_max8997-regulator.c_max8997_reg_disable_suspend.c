#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_2__* desc; int /*<<< orphan*/  dev; } ;
struct max8997_data {int* saved_states; TYPE_1__* iodev; } ;
struct i2c_client {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct i2c_client* i2c; } ;

/* Variables and functions */
 int MAX8997_LDO1 ; 
 int MAX8997_LDO10 ; 
 int MAX8997_LDO21 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int max8997_get_enable_register (struct regulator_dev*,int*,int*,int*) ; 
 int /*<<< orphan*/  max8997_read_reg (struct i2c_client*,int,int*) ; 
 int max8997_update_reg (struct i2c_client*,int,int,int) ; 
 struct max8997_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int max8997_reg_disable_suspend(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret, reg, mask, pattern;
	int rid = rdev_get_id(rdev);

	ret = max8997_get_enable_register(rdev, &reg, &mask, &pattern);
	if (ret)
		return ret;

	max8997_read_reg(i2c, reg, &max8997->saved_states[rid]);

	if (rid == MAX8997_LDO1 ||
			rid == MAX8997_LDO10 ||
			rid == MAX8997_LDO21) {
		dev_dbg(&rdev->dev, "Conditional Power-Off for %s\n",
				rdev->desc->name);
		return max8997_update_reg(i2c, reg, 0x40, mask);
	}

	dev_dbg(&rdev->dev, "Full Power-Off for %s (%xh -> %xh)\n",
			rdev->desc->name, max8997->saved_states[rid] & mask,
			(~pattern) & mask);
	return max8997_update_reg(i2c, reg, ~pattern, mask);
}