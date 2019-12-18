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
struct pinctrl_dev {int dummy; } ;
struct intel_pingroup {int /*<<< orphan*/  mode; scalar_t__ modes; } ;
struct intel_function {int /*<<< orphan*/  name; } ;
struct byt_gpio {TYPE_1__* soc_data; } ;
struct TYPE_2__ {struct intel_pingroup* groups; struct intel_function* functions; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYT_DEFAULT_GPIO_MUX ; 
 int /*<<< orphan*/  byt_set_group_mixed_mux (struct byt_gpio*,struct intel_pingroup const,scalar_t__) ; 
 int /*<<< orphan*/  byt_set_group_simple_mux (struct byt_gpio*,struct intel_pingroup const,int /*<<< orphan*/ ) ; 
 struct byt_gpio* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int byt_set_mux(struct pinctrl_dev *pctldev, unsigned int func_selector,
		       unsigned int group_selector)
{
	struct byt_gpio *vg = pinctrl_dev_get_drvdata(pctldev);
	const struct intel_function func = vg->soc_data->functions[func_selector];
	const struct intel_pingroup group = vg->soc_data->groups[group_selector];

	if (group.modes)
		byt_set_group_mixed_mux(vg, group, group.modes);
	else if (!strcmp(func.name, "gpio"))
		byt_set_group_simple_mux(vg, group, BYT_DEFAULT_GPIO_MUX);
	else
		byt_set_group_simple_mux(vg, group, group.mode);

	return 0;
}