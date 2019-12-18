#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int MAX77802_BUCK4 ; 
 int /*<<< orphan*/  MAX77802_RAMP_RATE_MASK_2BIT ; 
 unsigned int MAX77802_RAMP_RATE_SHIFT_2BIT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 unsigned int max77802_find_ramp_value (struct regulator_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ramp_table_77802_2bit ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max77802_set_ramp_delay_2bit(struct regulator_dev *rdev,
					int ramp_delay)
{
	int id = rdev_get_id(rdev);
	unsigned int ramp_value;

	if (id > MAX77802_BUCK4) {
		dev_warn(&rdev->dev,
			 "%s: regulator: ramp delay not supported\n",
			 rdev->desc->name);
		return -EINVAL;
	}
	ramp_value = max77802_find_ramp_value(rdev, ramp_table_77802_2bit,
				ARRAY_SIZE(ramp_table_77802_2bit), ramp_delay);

	return regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  MAX77802_RAMP_RATE_MASK_2BIT,
				  ramp_value << MAX77802_RAMP_RATE_SHIFT_2BIT);
}