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
struct meson_pmx_group {int num_pins; int /*<<< orphan*/ * pins; int /*<<< orphan*/  name; } ;
struct meson_pinctrl {int /*<<< orphan*/  dev; TYPE_1__* data; } ;
struct TYPE_2__ {struct meson_pmx_group* groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_pinconf_set (struct pinctrl_dev*,int /*<<< orphan*/ ,unsigned long*,unsigned int) ; 
 struct meson_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int meson_pinconf_group_set(struct pinctrl_dev *pcdev,
				   unsigned int num_group,
				   unsigned long *configs, unsigned num_configs)
{
	struct meson_pinctrl *pc = pinctrl_dev_get_drvdata(pcdev);
	struct meson_pmx_group *group = &pc->data->groups[num_group];
	int i;

	dev_dbg(pc->dev, "set pinconf for group %s\n", group->name);

	for (i = 0; i < group->num_pins; i++) {
		meson_pinconf_set(pcdev, group->pins[i], configs,
				  num_configs);
	}

	return 0;
}