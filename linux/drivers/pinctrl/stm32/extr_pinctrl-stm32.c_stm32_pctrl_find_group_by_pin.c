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
typedef  scalar_t__ u32 ;
struct stm32_pinctrl_group {scalar_t__ pin; } ;
struct stm32_pinctrl {int ngroups; struct stm32_pinctrl_group* groups; } ;

/* Variables and functions */

__attribute__((used)) static struct stm32_pinctrl_group *
stm32_pctrl_find_group_by_pin(struct stm32_pinctrl *pctl, u32 pin)
{
	int i;

	for (i = 0; i < pctl->ngroups; i++) {
		struct stm32_pinctrl_group *grp = pctl->groups + i;

		if (grp->pin == pin)
			return grp;
	}

	return NULL;
}