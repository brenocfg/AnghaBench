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
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsel_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD9571MWV_AVS_VD09_VID (int) ; 
 int bd9571mwv_avs_get_moni_state (struct regulator_dev*) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int bd9571mwv_avs_set_voltage_sel_regmap(struct regulator_dev *rdev,
						unsigned int sel)
{
	int ret;

	ret = bd9571mwv_avs_get_moni_state(rdev);
	if (ret < 0)
		return ret;

	return regmap_write_bits(rdev->regmap, BD9571MWV_AVS_VD09_VID(ret),
				 rdev->desc->vsel_mask, sel);
}