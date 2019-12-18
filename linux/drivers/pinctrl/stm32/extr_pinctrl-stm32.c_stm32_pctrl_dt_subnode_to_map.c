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
typedef  struct device_node* u32 ;
struct stm32_pinctrl_group {int /*<<< orphan*/  name; } ;
struct stm32_pinctrl {int /*<<< orphan*/  dev; } ;
struct property {int length; } ;
struct pinctrl_map {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PIN_MAP_TYPE_CONFIGS_GROUP ; 
 struct device_node* STM32_GET_PIN_FUNC (struct device_node*) ; 
 struct device_node* STM32_GET_PIN_NO (struct device_node*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,struct device_node**) ; 
 int pinconf_generic_parse_dt_config (struct device_node*,struct pinctrl_dev*,unsigned long**,unsigned int*) ; 
 struct stm32_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int pinctrl_utils_add_map_configs (struct pinctrl_dev*,struct pinctrl_map**,unsigned int*,unsigned int*,int /*<<< orphan*/ ,unsigned long*,unsigned int,int /*<<< orphan*/ ) ; 
 int pinctrl_utils_reserve_map (struct pinctrl_dev*,struct pinctrl_map**,unsigned int*,unsigned int*,unsigned int) ; 
 int stm32_pctrl_dt_node_to_map_func (struct stm32_pinctrl*,struct device_node*,struct device_node*,struct stm32_pinctrl_group*,struct pinctrl_map**,unsigned int*,unsigned int*) ; 
 struct stm32_pinctrl_group* stm32_pctrl_find_group_by_pin (struct stm32_pinctrl*,struct device_node*) ; 
 int /*<<< orphan*/  stm32_pctrl_is_function_valid (struct stm32_pinctrl*,struct device_node*,struct device_node*) ; 

__attribute__((used)) static int stm32_pctrl_dt_subnode_to_map(struct pinctrl_dev *pctldev,
				      struct device_node *node,
				      struct pinctrl_map **map,
				      unsigned *reserved_maps,
				      unsigned *num_maps)
{
	struct stm32_pinctrl *pctl;
	struct stm32_pinctrl_group *grp;
	struct property *pins;
	u32 pinfunc, pin, func;
	unsigned long *configs;
	unsigned int num_configs;
	bool has_config = 0;
	unsigned reserve = 0;
	int num_pins, num_funcs, maps_per_pin, i, err = 0;

	pctl = pinctrl_dev_get_drvdata(pctldev);

	pins = of_find_property(node, "pinmux", NULL);
	if (!pins) {
		dev_err(pctl->dev, "missing pins property in node %pOFn .\n",
				node);
		return -EINVAL;
	}

	err = pinconf_generic_parse_dt_config(node, pctldev, &configs,
		&num_configs);
	if (err)
		return err;

	if (num_configs)
		has_config = 1;

	num_pins = pins->length / sizeof(u32);
	num_funcs = num_pins;
	maps_per_pin = 0;
	if (num_funcs)
		maps_per_pin++;
	if (has_config && num_pins >= 1)
		maps_per_pin++;

	if (!num_pins || !maps_per_pin) {
		err = -EINVAL;
		goto exit;
	}

	reserve = num_pins * maps_per_pin;

	err = pinctrl_utils_reserve_map(pctldev, map,
			reserved_maps, num_maps, reserve);
	if (err)
		goto exit;

	for (i = 0; i < num_pins; i++) {
		err = of_property_read_u32_index(node, "pinmux",
				i, &pinfunc);
		if (err)
			goto exit;

		pin = STM32_GET_PIN_NO(pinfunc);
		func = STM32_GET_PIN_FUNC(pinfunc);

		if (!stm32_pctrl_is_function_valid(pctl, pin, func)) {
			dev_err(pctl->dev, "invalid function.\n");
			err = -EINVAL;
			goto exit;
		}

		grp = stm32_pctrl_find_group_by_pin(pctl, pin);
		if (!grp) {
			dev_err(pctl->dev, "unable to match pin %d to group\n",
					pin);
			err = -EINVAL;
			goto exit;
		}

		err = stm32_pctrl_dt_node_to_map_func(pctl, pin, func, grp, map,
				reserved_maps, num_maps);
		if (err)
			goto exit;

		if (has_config) {
			err = pinctrl_utils_add_map_configs(pctldev, map,
					reserved_maps, num_maps, grp->name,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_GROUP);
			if (err)
				goto exit;
		}
	}

exit:
	kfree(configs);
	return err;
}