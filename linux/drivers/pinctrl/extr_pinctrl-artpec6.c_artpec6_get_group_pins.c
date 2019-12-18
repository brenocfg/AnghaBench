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
struct TYPE_2__ {unsigned int num_pins; scalar_t__ pins; } ;

/* Variables and functions */
 TYPE_1__* artpec6_pin_groups ; 

__attribute__((used)) static int artpec6_get_group_pins(struct pinctrl_dev *pctldev,
				  unsigned int group,
				  const unsigned int **pins,
				  unsigned int *num_pins)
{
	*pins = (unsigned int *)artpec6_pin_groups[group].pins;
	*num_pins = artpec6_pin_groups[group].num_pins;
	return 0;
}