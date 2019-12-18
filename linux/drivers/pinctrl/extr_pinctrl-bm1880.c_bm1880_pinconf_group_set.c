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
struct bm1880_pinctrl {struct bm1880_pctrl_group* groups; } ;
struct bm1880_pctrl_group {int npins; int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 int bm1880_pinconf_cfg_set (struct pinctrl_dev*,int /*<<< orphan*/ ,unsigned long*,unsigned int) ; 
 struct bm1880_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int bm1880_pinconf_group_set(struct pinctrl_dev *pctldev,
				    unsigned int selector,
				    unsigned long *configs,
				    unsigned int  num_configs)
{
	int i, ret;
	struct bm1880_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	const struct bm1880_pctrl_group *pgrp = &pctrl->groups[selector];

	for (i = 0; i < pgrp->npins; i++) {
		ret = bm1880_pinconf_cfg_set(pctldev, pgrp->pins[i], configs,
					     num_configs);
		if (ret)
			return ret;
	}

	return 0;
}