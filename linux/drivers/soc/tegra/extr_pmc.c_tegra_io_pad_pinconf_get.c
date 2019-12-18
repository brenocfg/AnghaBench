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
struct tegra_pmc {int dummy; } ;
struct tegra_io_pad_soc {int /*<<< orphan*/  id; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_LOW_POWER_MODE 129 
#define  PIN_CONFIG_POWER_SOURCE 128 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct tegra_pmc* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct tegra_io_pad_soc* tegra_io_pad_find (struct tegra_pmc*,unsigned int) ; 
 int tegra_io_pad_get_voltage (struct tegra_pmc*,int /*<<< orphan*/ ) ; 
 int tegra_io_pad_is_powered (struct tegra_pmc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_io_pad_pinconf_get(struct pinctrl_dev *pctl_dev,
				    unsigned int pin, unsigned long *config)
{
	enum pin_config_param param = pinconf_to_config_param(*config);
	struct tegra_pmc *pmc = pinctrl_dev_get_drvdata(pctl_dev);
	const struct tegra_io_pad_soc *pad;
	int ret;
	u32 arg;

	pad = tegra_io_pad_find(pmc, pin);
	if (!pad)
		return -EINVAL;

	switch (param) {
	case PIN_CONFIG_POWER_SOURCE:
		ret = tegra_io_pad_get_voltage(pmc, pad->id);
		if (ret < 0)
			return ret;

		arg = ret;
		break;

	case PIN_CONFIG_LOW_POWER_MODE:
		ret = tegra_io_pad_is_powered(pmc, pad->id);
		if (ret < 0)
			return ret;

		arg = !ret;
		break;

	default:
		return -EINVAL;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}