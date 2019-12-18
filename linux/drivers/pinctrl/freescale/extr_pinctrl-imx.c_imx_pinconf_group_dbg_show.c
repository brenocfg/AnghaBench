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
struct seq_file {int dummy; } ;
struct pinctrl_dev {unsigned int num_groups; } ;
struct imx_pin {int /*<<< orphan*/  pin; } ;
struct group_desc {int num_pins; scalar_t__ data; } ;

/* Variables and functions */
 int imx_pinconf_get (struct pinctrl_dev*,int /*<<< orphan*/ ,unsigned long*) ; 
 char* pin_get_name (struct pinctrl_dev*,int /*<<< orphan*/ ) ; 
 struct group_desc* pinctrl_generic_get_group (struct pinctrl_dev*,unsigned int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,unsigned long) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void imx_pinconf_group_dbg_show(struct pinctrl_dev *pctldev,
					 struct seq_file *s, unsigned group)
{
	struct group_desc *grp;
	unsigned long config;
	const char *name;
	int i, ret;

	if (group >= pctldev->num_groups)
		return;

	seq_puts(s, "\n");
	grp = pinctrl_generic_get_group(pctldev, group);
	if (!grp)
		return;

	for (i = 0; i < grp->num_pins; i++) {
		struct imx_pin *pin = &((struct imx_pin *)(grp->data))[i];

		name = pin_get_name(pctldev, pin->pin);
		ret = imx_pinconf_get(pctldev, pin->pin, &config);
		if (ret)
			return;
		seq_printf(s, "  %s: 0x%lx\n", name, config);
	}
}