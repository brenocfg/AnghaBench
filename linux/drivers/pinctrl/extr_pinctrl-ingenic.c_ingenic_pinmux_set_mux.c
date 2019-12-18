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
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct ingenic_pinctrl {int dummy; } ;
struct group_desc {unsigned int num_pins; int* data; int /*<<< orphan*/ * pins; int /*<<< orphan*/  name; } ;
struct function_desc {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ingenic_pinmux_set_pin_fn (struct ingenic_pinctrl*,int /*<<< orphan*/ ,int) ; 
 struct ingenic_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct group_desc* pinctrl_generic_get_group (struct pinctrl_dev*,unsigned int) ; 
 struct function_desc* pinmux_generic_get_function (struct pinctrl_dev*,unsigned int) ; 

__attribute__((used)) static int ingenic_pinmux_set_mux(struct pinctrl_dev *pctldev,
		unsigned int selector, unsigned int group)
{
	struct ingenic_pinctrl *jzpc = pinctrl_dev_get_drvdata(pctldev);
	struct function_desc *func;
	struct group_desc *grp;
	unsigned int i;

	func = pinmux_generic_get_function(pctldev, selector);
	if (!func)
		return -EINVAL;

	grp = pinctrl_generic_get_group(pctldev, group);
	if (!grp)
		return -EINVAL;

	dev_dbg(pctldev->dev, "enable function %s group %s\n",
		func->name, grp->name);

	for (i = 0; i < grp->num_pins; i++) {
		int *pin_modes = grp->data;

		ingenic_pinmux_set_pin_fn(jzpc, grp->pins[i], pin_modes[i]);
	}

	return 0;
}