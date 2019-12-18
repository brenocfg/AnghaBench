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
struct stpmic1_regulator_cfg {int /*<<< orphan*/  icc_mask; int /*<<< orphan*/  icc_reg; } ;
struct regulator_dev {int dummy; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 struct stpmic1_regulator_cfg* rdev_get_drvdata (struct regulator_dev*) ; 
 struct regmap* rdev_get_regmap (struct regulator_dev*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stpmic1_set_icc(struct regulator_dev *rdev)
{
	struct stpmic1_regulator_cfg *cfg = rdev_get_drvdata(rdev);
	struct regmap *regmap = rdev_get_regmap(rdev);

	/* enable switch off in case of over current */
	return regmap_update_bits(regmap, cfg->icc_reg, cfg->icc_mask,
				  cfg->icc_mask);
}