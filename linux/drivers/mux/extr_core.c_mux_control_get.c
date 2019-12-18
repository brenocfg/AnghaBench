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
struct of_phandle_args {int args_count; unsigned int* args; int /*<<< orphan*/  np; } ;
struct mux_control {int dummy; } ;
struct mux_chip {int controllers; struct mux_control* mux; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 struct mux_control* ERR_PTR (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,...) ; 
 struct mux_chip* of_find_mux_chip_by_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 int of_property_match_string (struct device_node*,char*,char const*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

struct mux_control *mux_control_get(struct device *dev, const char *mux_name)
{
	struct device_node *np = dev->of_node;
	struct of_phandle_args args;
	struct mux_chip *mux_chip;
	unsigned int controller;
	int index = 0;
	int ret;

	if (mux_name) {
		index = of_property_match_string(np, "mux-control-names",
						 mux_name);
		if (index < 0) {
			dev_err(dev, "mux controller '%s' not found\n",
				mux_name);
			return ERR_PTR(index);
		}
	}

	ret = of_parse_phandle_with_args(np,
					 "mux-controls", "#mux-control-cells",
					 index, &args);
	if (ret) {
		dev_err(dev, "%pOF: failed to get mux-control %s(%i)\n",
			np, mux_name ?: "", index);
		return ERR_PTR(ret);
	}

	mux_chip = of_find_mux_chip_by_node(args.np);
	of_node_put(args.np);
	if (!mux_chip)
		return ERR_PTR(-EPROBE_DEFER);

	if (args.args_count > 1 ||
	    (!args.args_count && (mux_chip->controllers > 1))) {
		dev_err(dev, "%pOF: wrong #mux-control-cells for %pOF\n",
			np, args.np);
		put_device(&mux_chip->dev);
		return ERR_PTR(-EINVAL);
	}

	controller = 0;
	if (args.args_count)
		controller = args.args[0];

	if (controller >= mux_chip->controllers) {
		dev_err(dev, "%pOF: bad mux controller %u specified in %pOF\n",
			np, controller, args.np);
		put_device(&mux_chip->dev);
		return ERR_PTR(-EINVAL);
	}

	return &mux_chip->mux[controller];
}