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
struct atmel_pioctrl {int npins; struct atmel_group* groups; } ;
struct atmel_group {unsigned int pin; } ;

/* Variables and functions */
 struct atmel_pioctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static struct atmel_group *
atmel_pctl_find_group_by_pin(struct pinctrl_dev *pctldev, unsigned pin)
{
	struct atmel_pioctrl *atmel_pioctrl = pinctrl_dev_get_drvdata(pctldev);
	int i;

	for (i = 0; i < atmel_pioctrl->npins; i++) {
		struct atmel_group *grp = atmel_pioctrl->groups + i;

		if (grp->pin == pin)
			return grp;
	}

	return NULL;
}