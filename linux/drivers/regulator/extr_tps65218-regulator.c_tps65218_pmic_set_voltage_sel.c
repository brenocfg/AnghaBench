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
struct tps65218 {int dummy; } ;
struct regulator_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {unsigned int vsel_mask; int /*<<< orphan*/  vsel_reg; } ;

/* Variables and functions */
#define  TPS65218_DCDC_1 129 
#define  TPS65218_DCDC_2 128 
 int /*<<< orphan*/  TPS65218_PROTECT_L1 ; 
 int /*<<< orphan*/  TPS65218_REG_CONTRL_SLEW_RATE ; 
 unsigned int TPS65218_SLEW_RATE_GO ; 
 struct tps65218* rdev_get_drvdata (struct regulator_dev*) ; 
 unsigned int rdev_get_id (struct regulator_dev*) ; 
 int tps65218_set_bits (struct tps65218*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65218_pmic_set_voltage_sel(struct regulator_dev *dev,
					 unsigned selector)
{
	int ret;
	struct tps65218 *tps = rdev_get_drvdata(dev);
	unsigned int rid = rdev_get_id(dev);

	/* Set the voltage based on vsel value and write protect level is 2 */
	ret = tps65218_set_bits(tps, dev->desc->vsel_reg, dev->desc->vsel_mask,
				selector, TPS65218_PROTECT_L1);

	/* Set GO bit for DCDC1/2 to initiate voltage transistion */
	switch (rid) {
	case TPS65218_DCDC_1:
	case TPS65218_DCDC_2:
		ret = tps65218_set_bits(tps, TPS65218_REG_CONTRL_SLEW_RATE,
					TPS65218_SLEW_RATE_GO,
					TPS65218_SLEW_RATE_GO,
					TPS65218_PROTECT_L1);
		break;
	}

	return ret;
}