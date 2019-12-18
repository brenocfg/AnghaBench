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
struct pinctrl_ops {int /*<<< orphan*/  get_group_name; int /*<<< orphan*/  get_groups_count; } ;
struct pinctrl_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {struct pinctrl_ops* pctlops; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int pinctrl_check_ops(struct pinctrl_dev *pctldev)
{
	const struct pinctrl_ops *ops = pctldev->desc->pctlops;

	if (!ops ||
	    !ops->get_groups_count ||
	    !ops->get_group_name)
		return -EINVAL;

	return 0;
}