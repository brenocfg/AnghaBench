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
typedef  int /*<<< orphan*/  u16 ;
struct spear_gpio_pingroup {int nmuxregs; TYPE_1__* muxregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */

void pmx_init_gpio_pingroup_addr(struct spear_gpio_pingroup *gpio_pingroup,
				 unsigned count, u16 reg)
{
	int i, j;

	for (i = 0; i < count; i++)
		for (j = 0; j < gpio_pingroup[i].nmuxregs; j++)
			gpio_pingroup[i].muxregs[j].reg = reg;
}