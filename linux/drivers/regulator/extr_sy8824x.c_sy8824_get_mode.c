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
struct sy8824_device_info {struct sy8824_config* cfg; } ;
struct sy8824_config {int /*<<< orphan*/  mode_reg; } ;
struct regulator_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 int SY8824C_MODE ; 
 struct sy8824_device_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned int sy8824_get_mode(struct regulator_dev *rdev)
{
	struct sy8824_device_info *di = rdev_get_drvdata(rdev);
	const struct sy8824_config *cfg = di->cfg;
	u32 val;
	int ret = 0;

	ret = regmap_read(rdev->regmap, cfg->mode_reg, &val);
	if (ret < 0)
		return ret;
	if (val & SY8824C_MODE)
		return REGULATOR_MODE_FAST;
	else
		return REGULATOR_MODE_NORMAL;
}