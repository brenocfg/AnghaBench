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
typedef  int u32 ;
struct regulator_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct mt6358_regulator_info {int qi; int /*<<< orphan*/  status_reg; } ;

/* Variables and functions */
 int REGULATOR_STATUS_OFF ; 
 int REGULATOR_STATUS_ON ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct mt6358_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mt6358_get_status(struct regulator_dev *rdev)
{
	int ret;
	u32 regval;
	struct mt6358_regulator_info *info = rdev_get_drvdata(rdev);

	ret = regmap_read(rdev->regmap, info->status_reg, &regval);
	if (ret != 0) {
		dev_info(&rdev->dev, "Failed to get enable reg: %d\n", ret);
		return ret;
	}

	return (regval & info->qi) ? REGULATOR_STATUS_ON : REGULATOR_STATUS_OFF;
}