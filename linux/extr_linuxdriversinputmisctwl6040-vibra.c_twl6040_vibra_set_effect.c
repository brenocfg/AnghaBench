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
typedef  int /*<<< orphan*/  u8 ;
struct vibra_info {int /*<<< orphan*/  direction; int /*<<< orphan*/  strong_speed; int /*<<< orphan*/  vibrmotor_res; int /*<<< orphan*/  vibrdrv_res; TYPE_1__* supplies; int /*<<< orphan*/  weak_speed; int /*<<< orphan*/  viblmotor_res; int /*<<< orphan*/  vibldrv_res; struct twl6040* twl6040; } ;
struct twl6040 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL6040_REG_VIBDATL ; 
 int /*<<< orphan*/  TWL6040_REG_VIBDATR ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_reg_write (struct twl6040*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_vibra_code (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl6040_vibra_set_effect(struct vibra_info *info)
{
	struct twl6040 *twl6040 = info->twl6040;
	u8 vibdatl, vibdatr;
	int volt;

	/* weak motor */
	volt = regulator_get_voltage(info->supplies[0].consumer) / 1000;
	vibdatl = twl6040_vibra_code(volt, info->vibldrv_res,
				     info->viblmotor_res,
				     info->weak_speed, info->direction);

	/* strong motor */
	volt = regulator_get_voltage(info->supplies[1].consumer) / 1000;
	vibdatr = twl6040_vibra_code(volt, info->vibrdrv_res,
				     info->vibrmotor_res,
				     info->strong_speed, info->direction);

	twl6040_reg_write(twl6040, TWL6040_REG_VIBDATL, vibdatl);
	twl6040_reg_write(twl6040, TWL6040_REG_VIBDATR, vibdatr);
}