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
typedef  int /*<<< orphan*/  u32 ;
struct property {int length; } ;
struct pinctrl_map {int dummy; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PIN_MAP_TYPE_CONFIGS_GROUP ; 
 int atmel_pctl_xlate_pinfunc (struct pinctrl_dev*,struct device_node*,int /*<<< orphan*/ ,char const**,char const**) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct device_node*) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 int pinconf_generic_parse_dt_config (struct device_node*,struct pinctrl_dev*,unsigned long**,unsigned int*) ; 
 int pinctrl_utils_add_map_configs (struct pinctrl_dev*,struct pinctrl_map**,unsigned int*,unsigned int*,char const*,unsigned long*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_utils_add_map_mux (struct pinctrl_dev*,struct pinctrl_map**,unsigned int*,unsigned int*,char const*,char const*) ; 
 int pinctrl_utils_reserve_map (struct pinctrl_dev*,struct pinctrl_map**,unsigned int*,unsigned int*,unsigned int) ; 

__attribute__((used)) static int atmel_pctl_dt_subnode_to_map(struct pinctrl_dev *pctldev,
					struct device_node *np,
					struct pinctrl_map **map,
					unsigned *reserved_maps,
					unsigned *num_maps)
{
	unsigned num_pins, num_configs, reserve;
	unsigned long *configs;
	struct property	*pins;
	u32 pinfunc;
	int ret, i;

	pins = of_find_property(np, "pinmux", NULL);
	if (!pins)
		return -EINVAL;

	ret = pinconf_generic_parse_dt_config(np, pctldev, &configs,
					      &num_configs);
	if (ret < 0) {
		dev_err(pctldev->dev, "%pOF: could not parse node property\n",
			np);
		return ret;
	}

	num_pins = pins->length / sizeof(u32);
	if (!num_pins) {
		dev_err(pctldev->dev, "no pins found in node %pOF\n", np);
		ret = -EINVAL;
		goto exit;
	}

	/*
	 * Reserve maps, at least there is a mux map and an optional conf
	 * map for each pin.
	 */
	reserve = 1;
	if (num_configs)
		reserve++;
	reserve *= num_pins;
	ret = pinctrl_utils_reserve_map(pctldev, map, reserved_maps, num_maps,
					reserve);
	if (ret < 0)
		goto exit;

	for (i = 0; i < num_pins; i++) {
		const char *group, *func;

		ret = of_property_read_u32_index(np, "pinmux", i, &pinfunc);
		if (ret)
			goto exit;

		ret = atmel_pctl_xlate_pinfunc(pctldev, np, pinfunc, &group,
					       &func);
		if (ret)
			goto exit;

		pinctrl_utils_add_map_mux(pctldev, map, reserved_maps, num_maps,
					  group, func);

		if (num_configs) {
			ret = pinctrl_utils_add_map_configs(pctldev, map,
					reserved_maps, num_maps, group,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_GROUP);
			if (ret < 0)
				goto exit;
		}
	}

exit:
	kfree(configs);
	return ret;
}