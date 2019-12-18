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
struct meson_pmx_group {int num_pins; int /*<<< orphan*/ * pins; int /*<<< orphan*/  name; scalar_t__ data; } ;
struct meson_pmx_func {int /*<<< orphan*/  name; } ;
struct meson_pmx_axg_data {int /*<<< orphan*/  func; } ;
struct meson_pinctrl {int /*<<< orphan*/  dev; TYPE_1__* data; } ;
struct TYPE_2__ {struct meson_pmx_group* groups; struct meson_pmx_func* funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int meson_axg_pmx_update_function (struct meson_pinctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct meson_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int meson_axg_pmx_set_mux(struct pinctrl_dev *pcdev,
			unsigned int func_num, unsigned int group_num)
{
	int i;
	int ret;
	struct meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);
	struct meson_pmx_func *func = &pc->data->funcs[func_num];
	struct meson_pmx_group *group = &pc->data->groups[group_num];
	struct meson_pmx_axg_data *pmx_data =
		(struct meson_pmx_axg_data *)group->data;

	dev_dbg(pc->dev, "enable function %s, group %s\n", func->name,
		group->name);

	for (i = 0; i < group->num_pins; i++) {
		ret = meson_axg_pmx_update_function(pc, group->pins[i],
			pmx_data->func);
		if (ret)
			return ret;
	}

	return 0;
}