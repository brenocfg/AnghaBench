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
typedef  size_t u32 ;
struct wmt_pinctrl_data {int /*<<< orphan*/ * groups; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  function; int /*<<< orphan*/  group; } ;
struct TYPE_4__ {TYPE_1__ mux; } ;
struct pinctrl_map {TYPE_2__ data; int /*<<< orphan*/  type; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PIN_MAP_TYPE_MUX_GROUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * wmt_functions ; 
 int wmt_pctl_find_group_by_pin (struct wmt_pinctrl_data*,size_t) ; 

__attribute__((used)) static int wmt_pctl_dt_node_to_map_func(struct wmt_pinctrl_data *data,
					struct device_node *np,
					u32 pin, u32 fnum,
					struct pinctrl_map **maps)
{
	int group;
	struct pinctrl_map *map = *maps;

	if (fnum >= ARRAY_SIZE(wmt_functions)) {
		dev_err(data->dev, "invalid wm,function %d\n", fnum);
		return -EINVAL;
	}

	group = wmt_pctl_find_group_by_pin(data, pin);
	if (group < 0) {
		dev_err(data->dev, "unable to match pin %d to group\n", pin);
		return group;
	}

	map->type = PIN_MAP_TYPE_MUX_GROUP;
	map->data.mux.group = data->groups[group];
	map->data.mux.function = wmt_functions[fnum];
	(*maps)++;

	return 0;
}