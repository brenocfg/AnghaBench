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
struct pinctrl_dev {TYPE_2__* desc; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct TYPE_3__ {unsigned int number; } ;

/* Variables and functions */

__attribute__((used)) static int tegra_xusb_padctl_get_group_pins(struct pinctrl_dev *pinctrl,
					    unsigned group,
					    const unsigned **pins,
					    unsigned *num_pins)
{
	/*
	 * For the tegra-xusb pad controller groups are synonomous
	 * with lanes/pins and there is always one lane/pin per group.
	 */
	*pins = &pinctrl->desc->pins[group].number;
	*num_pins = 1;

	return 0;
}