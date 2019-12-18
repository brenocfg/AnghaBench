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
struct armada_37xx_pinctrl {TYPE_1__* funcs; struct armada_37xx_pin_group* groups; } ;
struct armada_37xx_pin_group {int dummy; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int armada_37xx_pmx_set_by_name (struct pinctrl_dev*,char const*,struct armada_37xx_pin_group*) ; 
 struct armada_37xx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int armada_37xx_pmx_set(struct pinctrl_dev *pctldev,
			       unsigned int selector,
			       unsigned int group)
{

	struct armada_37xx_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	struct armada_37xx_pin_group *grp = &info->groups[group];
	const char *name = info->funcs[selector].name;

	return armada_37xx_pmx_set_by_name(pctldev, name, grp);
}