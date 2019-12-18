#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  group_or_pin; int /*<<< orphan*/  num_configs; int /*<<< orphan*/  configs; } ;
struct TYPE_6__ {TYPE_2__ configs; } ;
struct pinctrl_setting {int type; TYPE_3__ data; struct pinctrl_dev* pctldev; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct pinconf_ops {int (* pin_config_set ) (struct pinctrl_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* pin_config_group_set ) (struct pinctrl_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct pinconf_ops* confops; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_MAP_TYPE_CONFIGS_GROUP 129 
#define  PIN_MAP_TYPE_CONFIGS_PIN 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int stub1 (struct pinctrl_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct pinctrl_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pinconf_apply_setting(const struct pinctrl_setting *setting)
{
	struct pinctrl_dev *pctldev = setting->pctldev;
	const struct pinconf_ops *ops = pctldev->desc->confops;
	int ret;

	if (!ops) {
		dev_err(pctldev->dev, "missing confops\n");
		return -EINVAL;
	}

	switch (setting->type) {
	case PIN_MAP_TYPE_CONFIGS_PIN:
		if (!ops->pin_config_set) {
			dev_err(pctldev->dev, "missing pin_config_set op\n");
			return -EINVAL;
		}
		ret = ops->pin_config_set(pctldev,
				setting->data.configs.group_or_pin,
				setting->data.configs.configs,
				setting->data.configs.num_configs);
		if (ret < 0) {
			dev_err(pctldev->dev,
				"pin_config_set op failed for pin %d\n",
				setting->data.configs.group_or_pin);
			return ret;
		}
		break;
	case PIN_MAP_TYPE_CONFIGS_GROUP:
		if (!ops->pin_config_group_set) {
			dev_err(pctldev->dev,
				"missing pin_config_group_set op\n");
			return -EINVAL;
		}
		ret = ops->pin_config_group_set(pctldev,
				setting->data.configs.group_or_pin,
				setting->data.configs.configs,
				setting->data.configs.num_configs);
		if (ret < 0) {
			dev_err(pctldev->dev,
				"pin_config_group_set op failed for group %d\n",
				setting->data.configs.group_or_pin);
			return ret;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}