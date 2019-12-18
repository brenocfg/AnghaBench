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
struct samsung_pmx_func {char const** groups; int num_groups; int /*<<< orphan*/  name; int /*<<< orphan*/  val; } ;
struct samsung_pinctrl_drv_data {int dummy; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 char const** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int of_property_count_strings (struct device_node*,char*) ; 
 int of_property_read_string_index (struct device_node*,char*,int,char const**) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int samsung_pinctrl_create_function(struct device *dev,
				struct samsung_pinctrl_drv_data *drvdata,
				struct device_node *func_np,
				struct samsung_pmx_func *func)
{
	int npins;
	int ret;
	int i;

	if (of_property_read_u32(func_np, "samsung,pin-function", &func->val))
		return 0;

	npins = of_property_count_strings(func_np, "samsung,pins");
	if (npins < 1) {
		dev_err(dev, "invalid pin list in %pOFn node", func_np);
		return -EINVAL;
	}

	func->name = func_np->full_name;

	func->groups = devm_kcalloc(dev, npins, sizeof(char *), GFP_KERNEL);
	if (!func->groups)
		return -ENOMEM;

	for (i = 0; i < npins; ++i) {
		const char *gname;

		ret = of_property_read_string_index(func_np, "samsung,pins",
							i, &gname);
		if (ret) {
			dev_err(dev,
				"failed to read pin name %d from %pOFn node\n",
				i, func_np);
			return ret;
		}

		func->groups[i] = gname;
	}

	func->num_groups = npins;
	return 1;
}