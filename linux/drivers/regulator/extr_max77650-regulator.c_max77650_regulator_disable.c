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
struct regmap {int dummy; } ;
struct max77650_regulator_desc {int /*<<< orphan*/  regB; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX77650_REGULATOR_DISABLED ; 
 int /*<<< orphan*/  MAX77650_REGULATOR_EN_CTRL_MASK ; 
 struct max77650_regulator_desc* rdev_get_drvdata (struct regulator_dev*) ; 
 struct regmap* rdev_get_regmap (struct regulator_dev*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77650_regulator_disable(struct regulator_dev *rdev)
{
	struct max77650_regulator_desc *rdesc;
	struct regmap *map;

	rdesc = rdev_get_drvdata(rdev);
	map = rdev_get_regmap(rdev);

	return regmap_update_bits(map, rdesc->regB,
				  MAX77650_REGULATOR_EN_CTRL_MASK,
				  MAX77650_REGULATOR_DISABLED);
}