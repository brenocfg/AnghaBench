#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct property {int length; } ;
struct pinctrl_map {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct mtk_pinctrl_group {int /*<<< orphan*/  name; } ;
struct mtk_pinctrl {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ npins; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ MTK_GET_PIN_FUNC (scalar_t__) ; 
 scalar_t__ MTK_GET_PIN_NO (scalar_t__) ; 
 int /*<<< orphan*/  PIN_MAP_TYPE_CONFIGS_GROUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 int /*<<< orphan*/  mtk_gpio_functions ; 
 int mtk_pctrl_dt_node_to_map_func (struct mtk_pinctrl*,scalar_t__,scalar_t__,struct mtk_pinctrl_group*,struct pinctrl_map**,unsigned int*,unsigned int*) ; 
 struct mtk_pinctrl_group* mtk_pctrl_find_group_by_pin (struct mtk_pinctrl*,scalar_t__) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,scalar_t__*) ; 
 int pinconf_generic_parse_dt_config (struct device_node*,struct pinctrl_dev*,unsigned long**,unsigned int*) ; 
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int pinctrl_utils_add_map_configs (struct pinctrl_dev*,struct pinctrl_map**,unsigned int*,unsigned int*,int /*<<< orphan*/ ,unsigned long*,unsigned int,int /*<<< orphan*/ ) ; 
 int pinctrl_utils_reserve_map (struct pinctrl_dev*,struct pinctrl_map**,unsigned int*,unsigned int*,unsigned int) ; 

__attribute__((used)) static int mtk_pctrl_dt_subnode_to_map(struct pinctrl_dev *pctldev,
				       struct device_node *node,
				       struct pinctrl_map **map,
				       unsigned *reserved_maps,
				       unsigned *num_maps)
{
	struct mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	int num_pins, num_funcs, maps_per_pin, i, err;
	struct mtk_pinctrl_group *grp;
	unsigned int num_configs;
	bool has_config = false;
	unsigned long *configs;
	u32 pinfunc, pin, func;
	struct property *pins;
	unsigned reserve = 0;

	pins = of_find_property(node, "pinmux", NULL);
	if (!pins) {
		dev_err(hw->dev, "missing pins property in node %pOFn .\n",
			node);
		return -EINVAL;
	}

	err = pinconf_generic_parse_dt_config(node, pctldev, &configs,
					      &num_configs);
	if (err)
		return err;

	if (num_configs)
		has_config = true;

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

	err = pinctrl_utils_reserve_map(pctldev, map, reserved_maps, num_maps,
					reserve);
	if (err < 0)
		goto exit;

	for (i = 0; i < num_pins; i++) {
		err = of_property_read_u32_index(node, "pinmux", i, &pinfunc);
		if (err)
			goto exit;

		pin = MTK_GET_PIN_NO(pinfunc);
		func = MTK_GET_PIN_FUNC(pinfunc);

		if (pin >= hw->soc->npins ||
		    func >= ARRAY_SIZE(mtk_gpio_functions)) {
			dev_err(hw->dev, "invalid pins value.\n");
			err = -EINVAL;
			goto exit;
		}

		grp = mtk_pctrl_find_group_by_pin(hw, pin);
		if (!grp) {
			dev_err(hw->dev, "unable to match pin %d to group\n",
				pin);
			err = -EINVAL;
			goto exit;
		}

		err = mtk_pctrl_dt_node_to_map_func(hw, pin, func, grp, map,
						    reserved_maps, num_maps);
		if (err < 0)
			goto exit;

		if (has_config) {
			err = pinctrl_utils_add_map_configs(pctldev, map,
							    reserved_maps,
							    num_maps,
							    grp->name,
							    configs,
							    num_configs,
							    PIN_MAP_TYPE_CONFIGS_GROUP);
			if (err < 0)
				goto exit;
		}
	}

	err = 0;

exit:
	kfree(configs);
	return err;
}