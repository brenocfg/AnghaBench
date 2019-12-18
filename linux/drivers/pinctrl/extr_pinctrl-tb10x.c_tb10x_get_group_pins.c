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
struct tb10x_pinctrl {TYPE_1__* pingroups; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {unsigned int* pins; unsigned int pincnt; } ;

/* Variables and functions */
 struct tb10x_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int tb10x_get_group_pins(struct pinctrl_dev *pctl, unsigned n,
				unsigned const **pins,
				unsigned * const num_pins)
{
	struct tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);

	*pins = state->pingroups[n].pins;
	*num_pins = state->pingroups[n].pincnt;

	return 0;
}