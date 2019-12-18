#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_pinctrl {int /*<<< orphan*/  dev; } ;
struct st_pctl_group {int npins; int /*<<< orphan*/  name; TYPE_1__* pin_conf; int /*<<< orphan*/ * pins; } ;
struct TYPE_7__ {int /*<<< orphan*/  function; int /*<<< orphan*/  group; } ;
struct TYPE_6__ {int num_configs; int /*<<< orphan*/ * configs; int /*<<< orphan*/  group_or_pin; } ;
struct TYPE_8__ {TYPE_3__ mux; TYPE_2__ configs; } ;
struct pinctrl_map {TYPE_4__ data; int /*<<< orphan*/  type; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct device_node {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIN_MAP_TYPE_CONFIGS_PIN ; 
 int /*<<< orphan*/  PIN_MAP_TYPE_MUX_GROUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct device_node*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pinctrl_map* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct pinctrl_map*) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pin_get_name (struct pinctrl_dev*,int /*<<< orphan*/ ) ; 
 struct st_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct st_pctl_group* st_pctl_find_group_by_name (struct st_pinctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_pctl_dt_node_to_map(struct pinctrl_dev *pctldev,
	struct device_node *np, struct pinctrl_map **map, unsigned *num_maps)
{
	struct st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	const struct st_pctl_group *grp;
	struct pinctrl_map *new_map;
	struct device_node *parent;
	int map_num, i;

	grp = st_pctl_find_group_by_name(info, np->name);
	if (!grp) {
		dev_err(info->dev, "unable to find group for node %pOFn\n",
			np);
		return -EINVAL;
	}

	map_num = grp->npins + 1;
	new_map = devm_kcalloc(pctldev->dev,
				map_num, sizeof(*new_map), GFP_KERNEL);
	if (!new_map)
		return -ENOMEM;

	parent = of_get_parent(np);
	if (!parent) {
		devm_kfree(pctldev->dev, new_map);
		return -EINVAL;
	}

	*map = new_map;
	*num_maps = map_num;
	new_map[0].type = PIN_MAP_TYPE_MUX_GROUP;
	new_map[0].data.mux.function = parent->name;
	new_map[0].data.mux.group = np->name;
	of_node_put(parent);

	/* create config map per pin */
	new_map++;
	for (i = 0; i < grp->npins; i++) {
		new_map[i].type = PIN_MAP_TYPE_CONFIGS_PIN;
		new_map[i].data.configs.group_or_pin =
				pin_get_name(pctldev, grp->pins[i]);
		new_map[i].data.configs.configs = &grp->pin_conf[i].config;
		new_map[i].data.configs.num_configs = 1;
	}
	dev_info(pctldev->dev, "maps: function %s group %s num %d\n",
		(*map)->data.mux.function, grp->name, map_num);

	return 0;
}