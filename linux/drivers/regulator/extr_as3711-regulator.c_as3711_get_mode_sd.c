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
struct regulator_dev {int /*<<< orphan*/  regmap; TYPE_1__* desc; } ;
struct TYPE_2__ {unsigned int enable_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3711_SD_CONTROL_1 ; 
 unsigned int EINVAL ; 
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int as3711_get_mode_sd(struct regulator_dev *rdev)
{
	unsigned int fast_bit = rdev->desc->enable_mask,
		low_noise_bit = fast_bit << 4, mask = fast_bit | low_noise_bit;
	unsigned int val;
	int ret = regmap_read(rdev->regmap, AS3711_SD_CONTROL_1, &val);

	if (ret < 0)
		return ret;

	if ((val & mask) == mask)
		return REGULATOR_MODE_FAST;

	if ((val & mask) == low_noise_bit)
		return REGULATOR_MODE_NORMAL;

	if (!(val & mask))
		return REGULATOR_MODE_IDLE;

	return -EINVAL;
}