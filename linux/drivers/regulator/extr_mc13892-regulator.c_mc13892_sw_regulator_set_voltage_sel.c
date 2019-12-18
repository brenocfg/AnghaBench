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
typedef  int u32 ;
struct regulator_dev {TYPE_1__* desc; } ;
struct mc13xxx_regulator_priv {int /*<<< orphan*/  mc13xxx; } ;
struct TYPE_4__ {int vsel_mask; scalar_t__ vsel_reg; } ;
struct TYPE_3__ {int* volt_table; } ;

/* Variables and functions */
 scalar_t__ MC13892_SWITCHERS0 ; 
 int MC13892_SWITCHERS0_SWxHI ; 
 scalar_t__ MC13892_SWxHI_SEL_OFFSET ; 
 TYPE_2__* mc13892_regulators ; 
 int /*<<< orphan*/  mc13xxx_lock (int /*<<< orphan*/ ) ; 
 int mc13xxx_reg_rmw (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  mc13xxx_unlock (int /*<<< orphan*/ ) ; 
 struct mc13xxx_regulator_priv* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int mc13892_sw_regulator_set_voltage_sel(struct regulator_dev *rdev,
						unsigned selector)
{
	struct mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	int volt, mask, id = rdev_get_id(rdev);
	u32 reg_value;
	int ret;

	volt = rdev->desc->volt_table[selector];
	mask = mc13892_regulators[id].vsel_mask;
	reg_value = selector;

	/*
	 * Don't mess with the HI bit or support HI voltage offsets for SW1.
	 *
	 * Since the get_voltage_sel callback has given a fudged value for
	 * the selector offset, we need to back out that offset if HI is
	 * to be set so we write the correct value to the register.
	 *
	 * The HI bit addition and selector offset handling COULD be more
	 * complicated by shifting and masking off the voltage selector part
	 * of the register then logical OR it back in, but since the selector
	 * is at bits 4:0 there is very little point. This makes the whole
	 * thing more readable and we do far less work.
	 */

	if (mc13892_regulators[id].vsel_reg != MC13892_SWITCHERS0) {
		mask |= MC13892_SWITCHERS0_SWxHI;

		if (volt > 1375000) {
			reg_value -= MC13892_SWxHI_SEL_OFFSET;
			reg_value |= MC13892_SWITCHERS0_SWxHI;
		} else {
			reg_value &= ~MC13892_SWITCHERS0_SWxHI;
		}
	}

	mc13xxx_lock(priv->mc13xxx);
	ret = mc13xxx_reg_rmw(priv->mc13xxx, mc13892_regulators[id].vsel_reg,
			      mask, reg_value);
	mc13xxx_unlock(priv->mc13xxx);

	return ret;
}