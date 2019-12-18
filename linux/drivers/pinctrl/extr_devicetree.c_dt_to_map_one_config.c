#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_ops {int (* dt_node_to_map ) (struct pinctrl_dev*,struct device_node*,struct pinctrl_map**,unsigned int*) ;} ;
struct pinctrl_map {int dummy; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct pinctrl {TYPE_2__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct TYPE_5__ {struct pinctrl_ops* pctlops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MODULES ; 
 int ENODEV ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int driver_deferred_probe_check_state (TYPE_2__*) ; 
 int driver_deferred_probe_check_state_continue (TYPE_2__*) ; 
 int dt_remember_or_free_map (struct pinctrl*,char const*,struct pinctrl_dev*,struct pinctrl_map*,unsigned int) ; 
 struct pinctrl_dev* get_pinctrl_dev_from_of_node (struct device_node*) ; 
 struct device_node* of_get_next_parent (struct device_node*) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 scalar_t__ of_node_is_root (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_bool (struct device_node*,char*) ; 
 int stub1 (struct pinctrl_dev*,struct device_node*,struct pinctrl_map**,unsigned int*) ; 

__attribute__((used)) static int dt_to_map_one_config(struct pinctrl *p,
				struct pinctrl_dev *hog_pctldev,
				const char *statename,
				struct device_node *np_config)
{
	struct pinctrl_dev *pctldev = NULL;
	struct device_node *np_pctldev;
	const struct pinctrl_ops *ops;
	int ret;
	struct pinctrl_map *map;
	unsigned num_maps;
	bool allow_default = false;

	/* Find the pin controller containing np_config */
	np_pctldev = of_node_get(np_config);
	for (;;) {
		if (!allow_default)
			allow_default = of_property_read_bool(np_pctldev,
							      "pinctrl-use-default");

		np_pctldev = of_get_next_parent(np_pctldev);
		if (!np_pctldev || of_node_is_root(np_pctldev)) {
			of_node_put(np_pctldev);
			/* keep deferring if modules are enabled unless we've timed out */
			if (IS_ENABLED(CONFIG_MODULES) && !allow_default)
				return driver_deferred_probe_check_state_continue(p->dev);

			return driver_deferred_probe_check_state(p->dev);
		}
		/* If we're creating a hog we can use the passed pctldev */
		if (hog_pctldev && (np_pctldev == p->dev->of_node)) {
			pctldev = hog_pctldev;
			break;
		}
		pctldev = get_pinctrl_dev_from_of_node(np_pctldev);
		if (pctldev)
			break;
		/* Do not defer probing of hogs (circular loop) */
		if (np_pctldev == p->dev->of_node) {
			of_node_put(np_pctldev);
			return -ENODEV;
		}
	}
	of_node_put(np_pctldev);

	/*
	 * Call pinctrl driver to parse device tree node, and
	 * generate mapping table entries
	 */
	ops = pctldev->desc->pctlops;
	if (!ops->dt_node_to_map) {
		dev_err(p->dev, "pctldev %s doesn't support DT\n",
			dev_name(pctldev->dev));
		return -ENODEV;
	}
	ret = ops->dt_node_to_map(pctldev, np_config, &map, &num_maps);
	if (ret < 0)
		return ret;

	/* Stash the mapping table chunk away for later use */
	return dt_remember_or_free_map(p, statename, pctldev, map, num_maps);
}