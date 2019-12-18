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
struct pinctrl_dev {int dummy; } ;
struct aspeed_pinctrl_data {int /*<<< orphan*/  scu; } ;
struct aspeed_pin_config_map {scalar_t__ arg; } ;
struct aspeed_pin_config {unsigned int bit; int /*<<< orphan*/  reg; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  MAP_TYPE_VAL ; 
 int const PIN_CONFIG_BIAS_PULL_DOWN ; 
 int const PIN_CONFIG_DRIVE_STRENGTH ; 
 struct aspeed_pin_config* find_pinconf_config (struct aspeed_pinctrl_data const*,unsigned int,int const) ; 
 struct aspeed_pin_config_map* find_pinconf_map (int const,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long pinconf_to_config_packed (int const,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct aspeed_pinctrl_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

int aspeed_pin_config_get(struct pinctrl_dev *pctldev, unsigned int offset,
		unsigned long *config)
{
	const enum pin_config_param param = pinconf_to_config_param(*config);
	const struct aspeed_pin_config_map *pmap;
	const struct aspeed_pinctrl_data *pdata;
	const struct aspeed_pin_config *pconf;
	unsigned int val;
	int rc = 0;
	u32 arg;

	pdata = pinctrl_dev_get_drvdata(pctldev);
	pconf = find_pinconf_config(pdata, offset, param);
	if (!pconf)
		return -ENOTSUPP;

	rc = regmap_read(pdata->scu, pconf->reg, &val);
	if (rc < 0)
		return rc;

	pmap = find_pinconf_map(param, MAP_TYPE_VAL,
			(val & BIT(pconf->bit)) >> pconf->bit);

	if (!pmap)
		return -EINVAL;

	if (param == PIN_CONFIG_DRIVE_STRENGTH)
		arg = (u32) pmap->arg;
	else if (param == PIN_CONFIG_BIAS_PULL_DOWN)
		arg = !!pmap->arg;
	else
		arg = 1;

	if (!arg)
		return -EINVAL;

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}