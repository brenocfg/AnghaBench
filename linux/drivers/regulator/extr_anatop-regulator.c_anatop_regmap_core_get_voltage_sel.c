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
struct anatop_regulator {int sel; scalar_t__ bypass; } ;

/* Variables and functions */
 int /*<<< orphan*/  anatop_regmap_is_enabled (struct regulator_dev*) ; 
 struct anatop_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regulator_get_voltage_sel_regmap (struct regulator_dev*) ; 

__attribute__((used)) static int anatop_regmap_core_get_voltage_sel(struct regulator_dev *reg)
{
	struct anatop_regulator *anatop_reg = rdev_get_drvdata(reg);

	if (anatop_reg->bypass || !anatop_regmap_is_enabled(reg))
		return anatop_reg->sel;

	return regulator_get_voltage_sel_regmap(reg);
}