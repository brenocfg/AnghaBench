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
struct ns_pinctrl {TYPE_1__* groups; } ;
struct TYPE_2__ {unsigned int* pins; unsigned int num_pins; } ;

/* Variables and functions */
 struct ns_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int ns_pinctrl_get_group_pins(struct pinctrl_dev *pctrl_dev,
				     unsigned int selector,
				     const unsigned int **pins,
				     unsigned int *num_pins)
{
	struct ns_pinctrl *ns_pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*pins = ns_pinctrl->groups[selector].pins;
	*num_pins = ns_pinctrl->groups[selector].num_pins;

	return 0;
}