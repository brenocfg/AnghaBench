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
typedef  unsigned int u8 ;
struct regulator_dev {int /*<<< orphan*/  regmap; TYPE_1__* desc; } ;
struct TYPE_2__ {unsigned int enable_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3711_SD_CONTROL_1 ; 
 int EINVAL ; 
#define  REGULATOR_MODE_FAST 130 
#define  REGULATOR_MODE_IDLE 129 
#define  REGULATOR_MODE_NORMAL 128 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int as3711_set_mode_sd(struct regulator_dev *rdev, unsigned int mode)
{
	unsigned int fast_bit = rdev->desc->enable_mask,
		low_noise_bit = fast_bit << 4;
	u8 val;

	switch (mode) {
	case REGULATOR_MODE_FAST:
		val = fast_bit | low_noise_bit;
		break;
	case REGULATOR_MODE_NORMAL:
		val = low_noise_bit;
		break;
	case REGULATOR_MODE_IDLE:
		val = 0;
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(rdev->regmap, AS3711_SD_CONTROL_1,
				  low_noise_bit | fast_bit, val);
}