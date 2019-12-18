#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct property {char* name; int /*<<< orphan*/ * value; } ;
struct pinctrl_dev {int dummy; } ;
struct pinctrl {TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  phandle ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,char*,int) ; 
 int dt_remember_dummy_state (struct pinctrl*,char const*) ; 
 int dt_to_map_one_config (struct pinctrl*,struct pinctrl_dev*,char const*,struct device_node*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 
 struct property* of_find_property (struct device_node*,char*,int*) ; 
 scalar_t__ of_have_populated_dt () ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_string_index (struct device_node*,char*,int,char const**) ; 
 int /*<<< orphan*/  pinctrl_dt_free_maps (struct pinctrl*) ; 
 int strlen (char*) ; 

int pinctrl_dt_to_map(struct pinctrl *p, struct pinctrl_dev *pctldev)
{
	struct device_node *np = p->dev->of_node;
	int state, ret;
	char *propname;
	struct property *prop;
	const char *statename;
	const __be32 *list;
	int size, config;
	phandle phandle;
	struct device_node *np_config;

	/* CONFIG_OF enabled, p->dev not instantiated from DT */
	if (!np) {
		if (of_have_populated_dt())
			dev_dbg(p->dev,
				"no of_node; not parsing pinctrl DT\n");
		return 0;
	}

	/* We may store pointers to property names within the node */
	of_node_get(np);

	/* For each defined state ID */
	for (state = 0; ; state++) {
		/* Retrieve the pinctrl-* property */
		propname = kasprintf(GFP_KERNEL, "pinctrl-%d", state);
		prop = of_find_property(np, propname, &size);
		kfree(propname);
		if (!prop) {
			if (state == 0) {
				of_node_put(np);
				return -ENODEV;
			}
			break;
		}
		list = prop->value;
		size /= sizeof(*list);

		/* Determine whether pinctrl-names property names the state */
		ret = of_property_read_string_index(np, "pinctrl-names",
						    state, &statename);
		/*
		 * If not, statename is just the integer state ID. But rather
		 * than dynamically allocate it and have to free it later,
		 * just point part way into the property name for the string.
		 */
		if (ret < 0)
			statename = prop->name + strlen("pinctrl-");

		/* For every referenced pin configuration node in it */
		for (config = 0; config < size; config++) {
			phandle = be32_to_cpup(list++);

			/* Look up the pin configuration node */
			np_config = of_find_node_by_phandle(phandle);
			if (!np_config) {
				dev_err(p->dev,
					"prop %s index %i invalid phandle\n",
					prop->name, config);
				ret = -EINVAL;
				goto err;
			}

			/* Parse the node */
			ret = dt_to_map_one_config(p, pctldev, statename,
						   np_config);
			of_node_put(np_config);
			if (ret < 0)
				goto err;
		}

		/* No entries in DT? Generate a dummy state table entry */
		if (!size) {
			ret = dt_remember_dummy_state(p, statename);
			if (ret < 0)
				goto err;
		}
	}

	return 0;

err:
	pinctrl_dt_free_maps(p);
	return ret;
}