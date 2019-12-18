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
typedef  int /*<<< orphan*/  u16 ;
struct pinctrl_dev {int dummy; } ;
struct palmas_pingroup {unsigned int* pins; int /*<<< orphan*/  name; struct palmas_pin_info** opt; } ;
struct palmas_pin_info {TYPE_2__* od_info; TYPE_1__* pud_info; } ;
struct palmas_pctrl_chip_info {int num_pin_groups; size_t* pins_current_opt; int /*<<< orphan*/  dev; int /*<<< orphan*/  palmas; struct palmas_pingroup* pin_groups; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_4__ {int od_reg_base; int od_reg_add; unsigned int od_mask; int od_disable; int od_enable; } ;
struct TYPE_3__ {int pullup_dn_reg_base; int pullup_dn_reg_add; unsigned int pullup_dn_mask; int normal_val; int pull_up_val; int pull_dn_val; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 131 
#define  PIN_CONFIG_BIAS_PULL_DOWN 130 
#define  PIN_CONFIG_BIAS_PULL_UP 129 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int palmas_read (int /*<<< orphan*/ ,int,int,unsigned int*) ; 
 unsigned long pinconf_to_config_packed (int,int /*<<< orphan*/ ) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct palmas_pctrl_chip_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int palmas_pinconf_get(struct pinctrl_dev *pctldev,
			unsigned pin, unsigned long *config)
{
	struct palmas_pctrl_chip_info *pci = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	const struct palmas_pingroup *g;
	const struct palmas_pin_info *opt;
	unsigned int val;
	int ret;
	int base, add;
	int rval;
	int arg;
	int group_nr;

	for (group_nr = 0; group_nr < pci->num_pin_groups; ++group_nr) {
		if (pci->pin_groups[group_nr].pins[0] == pin)
			break;
	}

	if (group_nr == pci->num_pin_groups) {
		dev_err(pci->dev,
			"Pinconf is not supported for pin-id %d\n", pin);
		return -ENOTSUPP;
	}

	g = &pci->pin_groups[group_nr];
	opt = g->opt[pci->pins_current_opt[group_nr]];
	if (!opt) {
		dev_err(pci->dev,
			"Pinconf is not supported for pin %s\n", g->name);
		return -ENOTSUPP;
	}

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (!opt->pud_info) {
			dev_err(pci->dev,
				"PULL control not supported for pin %s\n",
				g->name);
			return -ENOTSUPP;
		}
		base = opt->pud_info->pullup_dn_reg_base;
		add = opt->pud_info->pullup_dn_reg_add;
		ret = palmas_read(pci->palmas, base, add, &val);
		if (ret < 0) {
			dev_err(pci->dev, "Reg 0x%02x read failed: %d\n",
				add, ret);
			return ret;
		}

		rval = val & opt->pud_info->pullup_dn_mask;
		arg = 0;
		if ((opt->pud_info->normal_val >= 0) &&
				(opt->pud_info->normal_val == rval) &&
				(param == PIN_CONFIG_BIAS_DISABLE))
			arg = 1;
		else if ((opt->pud_info->pull_up_val >= 0) &&
				(opt->pud_info->pull_up_val == rval) &&
				(param == PIN_CONFIG_BIAS_PULL_UP))
			arg = 1;
		else if ((opt->pud_info->pull_dn_val >= 0) &&
				(opt->pud_info->pull_dn_val == rval) &&
				(param == PIN_CONFIG_BIAS_PULL_DOWN))
			arg = 1;
		break;

	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		if (!opt->od_info) {
			dev_err(pci->dev,
				"OD control not supported for pin %s\n",
				g->name);
			return -ENOTSUPP;
		}
		base = opt->od_info->od_reg_base;
		add = opt->od_info->od_reg_add;
		ret = palmas_read(pci->palmas, base, add, &val);
		if (ret < 0) {
			dev_err(pci->dev, "Reg 0x%02x read failed: %d\n",
				add, ret);
			return ret;
		}
		rval = val & opt->od_info->od_mask;
		arg = -1;
		if ((opt->od_info->od_disable >= 0) &&
				(opt->od_info->od_disable == rval))
			arg = 0;
		else if ((opt->od_info->od_enable >= 0) &&
					(opt->od_info->od_enable == rval))
			arg = 1;
		if (arg < 0) {
			dev_err(pci->dev,
				"OD control not supported for pin %s\n",
				g->name);
			return -ENOTSUPP;
		}
		break;

	default:
		dev_err(pci->dev, "Properties not supported\n");
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, (u16)arg);
	return 0;
}