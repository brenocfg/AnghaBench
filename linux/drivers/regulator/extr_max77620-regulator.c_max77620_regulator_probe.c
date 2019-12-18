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
struct regulator_dev {int dummy; } ;
struct regulator_desc {int /*<<< orphan*/  name; } ;
struct regulator_config {struct max77620_regulator* driver_data; struct device* dev; int /*<<< orphan*/  regmap; } ;
struct device {TYPE_2__* parent; scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct max77620_regulator_info {struct regulator_desc desc; } ;
struct max77620_regulator {TYPE_1__* reg_pdata; int /*<<< orphan*/ * enable_power_mode; struct max77620_regulator_info** rinfo; int /*<<< orphan*/  rmap; struct device* dev; } ;
struct max77620_chip {int chip_id; int /*<<< orphan*/  rmap; } ;
struct TYPE_4__ {scalar_t__ of_node; } ;
struct TYPE_3__ {int active_fps_src; int active_fps_pd_slot; int active_fps_pu_slot; int suspend_fps_src; int suspend_fps_pd_slot; int suspend_fps_pu_slot; int power_ok; int ramp_rate_setting; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
#define  MAX20024 130 
#define  MAX77620 129 
 int MAX77620_NUM_REGS ; 
 int /*<<< orphan*/  MAX77620_POWER_MODE_NORMAL ; 
 int MAX77620_REGULATOR_ID_SD4 ; 
#define  MAX77663 128 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 struct max77620_chip* dev_get_drvdata (TYPE_2__*) ; 
 struct max77620_regulator* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (struct device*,struct regulator_desc*,struct regulator_config*) ; 
 struct max77620_regulator_info* max20024_regs_info ; 
 int max77620_read_slew_rate (struct max77620_regulator*,int) ; 
 struct max77620_regulator_info* max77620_regs_info ; 
 struct max77620_regulator_info* max77663_regs_info ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max77620_regulator*) ; 

__attribute__((used)) static int max77620_regulator_probe(struct platform_device *pdev)
{
	struct max77620_chip *max77620_chip = dev_get_drvdata(pdev->dev.parent);
	struct max77620_regulator_info *rinfo;
	struct device *dev = &pdev->dev;
	struct regulator_config config = { };
	struct max77620_regulator *pmic;
	int ret = 0;
	int id;

	pmic = devm_kzalloc(dev, sizeof(*pmic), GFP_KERNEL);
	if (!pmic)
		return -ENOMEM;

	platform_set_drvdata(pdev, pmic);
	pmic->dev = dev;
	pmic->rmap = max77620_chip->rmap;
	if (!dev->of_node)
		dev->of_node = pdev->dev.parent->of_node;

	switch (max77620_chip->chip_id) {
	case MAX77620:
		rinfo = max77620_regs_info;
		break;
	case MAX20024:
		rinfo = max20024_regs_info;
		break;
	case MAX77663:
		rinfo = max77663_regs_info;
		break;
	default:
		return -EINVAL;
	}

	config.regmap = pmic->rmap;
	config.dev = dev;
	config.driver_data = pmic;

	for (id = 0; id < MAX77620_NUM_REGS; id++) {
		struct regulator_dev *rdev;
		struct regulator_desc *rdesc;

		if ((max77620_chip->chip_id == MAX77620) &&
		    (id == MAX77620_REGULATOR_ID_SD4))
			continue;

		rdesc = &rinfo[id].desc;
		pmic->rinfo[id] = &rinfo[id];
		pmic->enable_power_mode[id] = MAX77620_POWER_MODE_NORMAL;
		pmic->reg_pdata[id].active_fps_src = -1;
		pmic->reg_pdata[id].active_fps_pd_slot = -1;
		pmic->reg_pdata[id].active_fps_pu_slot = -1;
		pmic->reg_pdata[id].suspend_fps_src = -1;
		pmic->reg_pdata[id].suspend_fps_pd_slot = -1;
		pmic->reg_pdata[id].suspend_fps_pu_slot = -1;
		pmic->reg_pdata[id].power_ok = -1;
		pmic->reg_pdata[id].ramp_rate_setting = -1;

		ret = max77620_read_slew_rate(pmic, id);
		if (ret < 0)
			return ret;

		rdev = devm_regulator_register(dev, rdesc, &config);
		if (IS_ERR(rdev)) {
			ret = PTR_ERR(rdev);
			dev_err(dev, "Regulator registration %s failed: %d\n",
				rdesc->name, ret);
			return ret;
		}
	}

	return 0;
}