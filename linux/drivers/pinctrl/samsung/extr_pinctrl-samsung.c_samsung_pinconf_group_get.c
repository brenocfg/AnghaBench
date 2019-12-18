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
struct samsung_pinctrl_drv_data {TYPE_1__* pin_groups; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {unsigned int* pins; } ;

/* Variables and functions */
 struct samsung_pinctrl_drv_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  samsung_pinconf_get (struct pinctrl_dev*,unsigned int const,unsigned long*) ; 

__attribute__((used)) static int samsung_pinconf_group_get(struct pinctrl_dev *pctldev,
				unsigned int group, unsigned long *config)
{
	struct samsung_pinctrl_drv_data *drvdata;
	const unsigned int *pins;

	drvdata = pinctrl_dev_get_drvdata(pctldev);
	pins = drvdata->pin_groups[group].pins;
	samsung_pinconf_get(pctldev, pins[0], config);
	return 0;
}