#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct ocelot_pinctrl {TYPE_2__* desc; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct TYPE_3__ {unsigned int number; } ;

/* Variables and functions */
 struct ocelot_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int ocelot_pctl_get_group_pins(struct pinctrl_dev *pctldev,
				      unsigned int group,
				      const unsigned int **pins,
				      unsigned int *num_pins)
{
	struct ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	*pins = &info->desc->pins[group].number;
	*num_pins = 1;

	return 0;
}