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
struct sprd_pinctrl {int /*<<< orphan*/  dev; } ;
struct sprd_pin_group {char* name; unsigned int* pins; } ;
struct pinctrl_map {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct device_node {int /*<<< orphan*/  name; } ;
typedef  enum pinctrl_map_type { ____Placeholder_pinctrl_map_type } pinctrl_map_type ;

/* Variables and functions */
 int EINVAL ; 
 int PIN_MAP_TYPE_CONFIGS_GROUP ; 
 int PIN_MAP_TYPE_CONFIGS_PIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 int /*<<< orphan*/  of_node_full_name (struct device_node*) ; 
 int of_property_count_strings (struct device_node*,char*) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 char* pin_get_name (struct pinctrl_dev*,unsigned int) ; 
 int pinconf_generic_parse_dt_config (struct device_node*,struct pinctrl_dev*,unsigned long**,unsigned int*) ; 
 struct sprd_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int pinctrl_utils_add_map_configs (struct pinctrl_dev*,struct pinctrl_map**,unsigned int*,unsigned int*,char const*,unsigned long*,unsigned int,int) ; 
 int pinctrl_utils_add_map_mux (struct pinctrl_dev*,struct pinctrl_map**,unsigned int*,unsigned int*,char*,char const*) ; 
 int pinctrl_utils_reserve_map (struct pinctrl_dev*,struct pinctrl_map**,unsigned int*,unsigned int*,unsigned int) ; 
 struct sprd_pin_group* sprd_pinctrl_find_group_by_name (struct sprd_pinctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_dt_node_to_map(struct pinctrl_dev *pctldev,
			       struct device_node *np,
			       struct pinctrl_map **map,
			       unsigned int *num_maps)
{
	struct sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	const struct sprd_pin_group *grp;
	unsigned long *configs = NULL;
	unsigned int num_configs = 0;
	unsigned int reserved_maps = 0;
	unsigned int reserve = 0;
	const char *function;
	enum pinctrl_map_type type;
	int ret;

	grp = sprd_pinctrl_find_group_by_name(pctl, np->name);
	if (!grp) {
		dev_err(pctl->dev, "unable to find group for node %s\n",
			of_node_full_name(np));
		return -EINVAL;
	}

	ret = of_property_count_strings(np, "pins");
	if (ret < 0)
		return ret;

	if (ret == 1)
		type = PIN_MAP_TYPE_CONFIGS_PIN;
	else
		type = PIN_MAP_TYPE_CONFIGS_GROUP;

	ret = of_property_read_string(np, "function", &function);
	if (ret < 0) {
		if (ret != -EINVAL)
			dev_err(pctl->dev,
				"%s: could not parse property function\n",
				of_node_full_name(np));
		function = NULL;
	}

	ret = pinconf_generic_parse_dt_config(np, pctldev, &configs,
					      &num_configs);
	if (ret < 0) {
		dev_err(pctl->dev, "%s: could not parse node property\n",
			of_node_full_name(np));
		return ret;
	}

	*map = NULL;
	*num_maps = 0;

	if (function != NULL)
		reserve++;
	if (num_configs)
		reserve++;

	ret = pinctrl_utils_reserve_map(pctldev, map, &reserved_maps,
					num_maps, reserve);
	if (ret < 0)
		goto out;

	if (function) {
		ret = pinctrl_utils_add_map_mux(pctldev, map,
						&reserved_maps, num_maps,
						grp->name, function);
		if (ret < 0)
			goto out;
	}

	if (num_configs) {
		const char *group_or_pin;
		unsigned int pin_id;

		if (type == PIN_MAP_TYPE_CONFIGS_PIN) {
			pin_id = grp->pins[0];
			group_or_pin = pin_get_name(pctldev, pin_id);
		} else {
			group_or_pin = grp->name;
		}

		ret = pinctrl_utils_add_map_configs(pctldev, map,
						    &reserved_maps, num_maps,
						    group_or_pin, configs,
						    num_configs, type);
	}

out:
	kfree(configs);
	return ret;
}