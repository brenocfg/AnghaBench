#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pinmux_ops {int (* get_function_groups ) (struct pinctrl_dev*,int,char const* const**,unsigned int*) ;} ;
struct TYPE_9__ {int func; int group; } ;
struct TYPE_10__ {TYPE_4__ mux; } ;
struct pinctrl_setting {TYPE_5__ data; struct pinctrl_dev* pctldev; } ;
struct TYPE_7__ {char* function; char* group; } ;
struct TYPE_8__ {TYPE_2__ mux; } ;
struct pinctrl_map {TYPE_3__ data; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct TYPE_6__ {struct pinmux_ops* pmxops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int match_string (char const* const*,unsigned int,char const*) ; 
 int pinctrl_get_group_selector (struct pinctrl_dev*,char const*) ; 
 int pinmux_func_name_to_selector (struct pinctrl_dev*,char*) ; 
 int stub1 (struct pinctrl_dev*,int,char const* const**,unsigned int*) ; 

int pinmux_map_to_setting(const struct pinctrl_map *map,
			  struct pinctrl_setting *setting)
{
	struct pinctrl_dev *pctldev = setting->pctldev;
	const struct pinmux_ops *pmxops = pctldev->desc->pmxops;
	char const * const *groups;
	unsigned num_groups;
	int ret;
	const char *group;

	if (!pmxops) {
		dev_err(pctldev->dev, "does not support mux function\n");
		return -EINVAL;
	}

	ret = pinmux_func_name_to_selector(pctldev, map->data.mux.function);
	if (ret < 0) {
		dev_err(pctldev->dev, "invalid function %s in map table\n",
			map->data.mux.function);
		return ret;
	}
	setting->data.mux.func = ret;

	ret = pmxops->get_function_groups(pctldev, setting->data.mux.func,
					  &groups, &num_groups);
	if (ret < 0) {
		dev_err(pctldev->dev, "can't query groups for function %s\n",
			map->data.mux.function);
		return ret;
	}
	if (!num_groups) {
		dev_err(pctldev->dev,
			"function %s can't be selected on any group\n",
			map->data.mux.function);
		return -EINVAL;
	}
	if (map->data.mux.group) {
		group = map->data.mux.group;
		ret = match_string(groups, num_groups, group);
		if (ret < 0) {
			dev_err(pctldev->dev,
				"invalid group \"%s\" for function \"%s\"\n",
				group, map->data.mux.function);
			return ret;
		}
	} else {
		group = groups[0];
	}

	ret = pinctrl_get_group_selector(pctldev, group);
	if (ret < 0) {
		dev_err(pctldev->dev, "invalid group %s in map table\n",
			map->data.mux.group);
		return ret;
	}
	setting->data.mux.group = ret;

	return 0;
}