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
struct atmel_pioctrl {TYPE_1__* groups; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 struct atmel_pioctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int atmel_pctl_get_group_pins(struct pinctrl_dev *pctldev,
				     unsigned selector, const unsigned **pins,
				     unsigned *num_pins)
{
	struct atmel_pioctrl *atmel_pioctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = (unsigned *)&atmel_pioctrl->groups[selector].pin;
	*num_pins = 1;

	return 0;
}