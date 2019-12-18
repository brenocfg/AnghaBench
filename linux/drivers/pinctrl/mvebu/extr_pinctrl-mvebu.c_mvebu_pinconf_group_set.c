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
struct mvebu_pinctrl_group {int /*<<< orphan*/ * pins; int /*<<< orphan*/  data; TYPE_1__* ctrl; } ;
struct mvebu_pinctrl {struct mvebu_pinctrl_group* groups; } ;
struct TYPE_2__ {int (* mpp_set ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct mvebu_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int mvebu_pinconf_group_set(struct pinctrl_dev *pctldev,
				unsigned gid, unsigned long *configs,
				unsigned num_configs)
{
	struct mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct mvebu_pinctrl_group *grp = &pctl->groups[gid];
	int i, ret;

	if (!grp->ctrl)
		return -EINVAL;

	for (i = 0; i < num_configs; i++) {
		ret = grp->ctrl->mpp_set(grp->data, grp->pins[0], configs[i]);
		if (ret)
			return ret;
	} /* for each config */

	return 0;
}