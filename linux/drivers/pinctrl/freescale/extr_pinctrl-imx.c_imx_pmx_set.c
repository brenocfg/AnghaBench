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
struct pinctrl_dev {int dummy; } ;
struct imx_pinctrl_soc_info {int flags; } ;
struct imx_pinctrl {int /*<<< orphan*/  dev; struct imx_pinctrl_soc_info* info; } ;
struct imx_pin {int dummy; } ;
struct group_desc {unsigned int num_pins; scalar_t__ data; int /*<<< orphan*/  name; } ;
struct function_desc {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int IMX_USE_SCU ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int imx_pmx_set_one_pin_mmio (struct imx_pinctrl*,struct imx_pin*) ; 
 struct imx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct group_desc* pinctrl_generic_get_group (struct pinctrl_dev*,unsigned int) ; 
 struct function_desc* pinmux_generic_get_function (struct pinctrl_dev*,unsigned int) ; 

__attribute__((used)) static int imx_pmx_set(struct pinctrl_dev *pctldev, unsigned selector,
		       unsigned group)
{
	struct imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	const struct imx_pinctrl_soc_info *info = ipctl->info;
	struct function_desc *func;
	struct group_desc *grp;
	struct imx_pin *pin;
	unsigned int npins;
	int i, err;

	/*
	 * Configure the mux mode for each pin in the group for a specific
	 * function.
	 */
	grp = pinctrl_generic_get_group(pctldev, group);
	if (!grp)
		return -EINVAL;

	func = pinmux_generic_get_function(pctldev, selector);
	if (!func)
		return -EINVAL;

	npins = grp->num_pins;

	dev_dbg(ipctl->dev, "enable function %s group %s\n",
		func->name, grp->name);

	for (i = 0; i < npins; i++) {
		/*
		 * For IMX_USE_SCU case, we postpone the mux setting
		 * until config is set as we can set them together
		 * in one IPC call
		 */
		pin = &((struct imx_pin *)(grp->data))[i];
		if (!(info->flags & IMX_USE_SCU)) {
			err = imx_pmx_set_one_pin_mmio(ipctl, pin);
			if (err)
				return err;
		}
	}

	return 0;
}