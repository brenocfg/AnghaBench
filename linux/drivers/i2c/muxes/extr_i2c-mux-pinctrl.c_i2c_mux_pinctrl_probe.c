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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct i2c_mux_pinctrl {struct i2c_adapter** states; struct i2c_adapter* pinctrl; } ;
struct i2c_mux_core {int mux_locked; int /*<<< orphan*/  deselect; TYPE_1__* parent; } ;
struct i2c_adapter {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct i2c_adapter*) ; 
 int PTR_ERR (struct i2c_adapter*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct i2c_adapter* devm_pinctrl_get (struct device*) ; 
 int i2c_mux_add_adapter (struct i2c_mux_core*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct i2c_mux_core* i2c_mux_alloc (struct i2c_adapter*,struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  i2c_mux_pinctrl_deselect ; 
 struct i2c_adapter* i2c_mux_pinctrl_parent_adapter (struct device*) ; 
 struct i2c_adapter* i2c_mux_pinctrl_root_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_mux_pinctrl_select ; 
 struct i2c_mux_pinctrl* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  i2c_put_adapter (struct i2c_adapter*) ; 
 struct i2c_adapter* i2c_root_adapter (int /*<<< orphan*/ *) ; 
 int of_property_count_strings (struct device_node*,char*) ; 
 int of_property_read_string_index (struct device_node*,char*,int,char const**) ; 
 struct i2c_adapter* pinctrl_lookup_state (struct i2c_adapter*,char const*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct i2c_mux_core*) ; 
 int /*<<< orphan*/  states ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  struct_size (struct i2c_mux_pinctrl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2c_mux_pinctrl_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct i2c_mux_core *muxc;
	struct i2c_mux_pinctrl *mux;
	struct i2c_adapter *parent;
	struct i2c_adapter *root;
	int num_names, i, ret;
	const char *name;

	num_names = of_property_count_strings(np, "pinctrl-names");
	if (num_names < 0) {
		dev_err(dev, "Cannot parse pinctrl-names: %d\n",
			num_names);
		return num_names;
	}

	parent = i2c_mux_pinctrl_parent_adapter(dev);
	if (IS_ERR(parent))
		return PTR_ERR(parent);

	muxc = i2c_mux_alloc(parent, dev, num_names,
			     struct_size(mux, states, num_names),
			     0, i2c_mux_pinctrl_select, NULL);
	if (!muxc) {
		ret = -ENOMEM;
		goto err_put_parent;
	}
	mux = i2c_mux_priv(muxc);

	platform_set_drvdata(pdev, muxc);

	mux->pinctrl = devm_pinctrl_get(dev);
	if (IS_ERR(mux->pinctrl)) {
		ret = PTR_ERR(mux->pinctrl);
		dev_err(dev, "Cannot get pinctrl: %d\n", ret);
		goto err_put_parent;
	}

	for (i = 0; i < num_names; i++) {
		ret = of_property_read_string_index(np, "pinctrl-names", i,
						    &name);
		if (ret < 0) {
			dev_err(dev, "Cannot parse pinctrl-names: %d\n", ret);
			goto err_put_parent;
		}

		mux->states[i] = pinctrl_lookup_state(mux->pinctrl, name);
		if (IS_ERR(mux->states[i])) {
			ret = PTR_ERR(mux->states[i]);
			dev_err(dev, "Cannot look up pinctrl state %s: %d\n",
				name, ret);
			goto err_put_parent;
		}

		if (strcmp(name, "idle"))
			continue;

		if (i != num_names - 1) {
			dev_err(dev, "idle state must be last\n");
			ret = -EINVAL;
			goto err_put_parent;
		}
		muxc->deselect = i2c_mux_pinctrl_deselect;
	}

	root = i2c_root_adapter(&muxc->parent->dev);

	muxc->mux_locked = true;
	for (i = 0; i < num_names; i++) {
		if (root != i2c_mux_pinctrl_root_adapter(mux->states[i])) {
			muxc->mux_locked = false;
			break;
		}
	}
	if (muxc->mux_locked)
		dev_info(dev, "mux-locked i2c mux\n");

	/* Do not add any adapter for the idle state (if it's there at all). */
	for (i = 0; i < num_names - !!muxc->deselect; i++) {
		ret = i2c_mux_add_adapter(muxc, 0, i, 0);
		if (ret)
			goto err_del_adapter;
	}

	return 0;

err_del_adapter:
	i2c_mux_del_adapters(muxc);
err_put_parent:
	i2c_put_adapter(parent);

	return ret;
}