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
struct meson_pmx_group {int num_pins; unsigned int* pins; scalar_t__ data; } ;
struct meson_pinctrl {int /*<<< orphan*/  reg_mux; TYPE_1__* data; } ;
struct meson8_pmx_data {int reg; int /*<<< orphan*/  bit; scalar_t__ is_gpio; } ;
struct TYPE_2__ {int num_groups; struct meson_pmx_group* groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson8_pmx_disable_other_groups(struct meson_pinctrl *pc,
					    unsigned int pin, int sel_group)
{
	struct meson_pmx_group *group;
	struct meson8_pmx_data *pmx_data;
	int i, j;

	for (i = 0; i < pc->data->num_groups; i++) {
		group = &pc->data->groups[i];
		pmx_data = (struct meson8_pmx_data *)group->data;
		if (pmx_data->is_gpio || i == sel_group)
			continue;

		for (j = 0; j < group->num_pins; j++) {
			if (group->pins[j] == pin) {
				/* We have found a group using the pin */
				regmap_update_bits(pc->reg_mux,
						   pmx_data->reg * 4,
						   BIT(pmx_data->bit), 0);
			}
		}
	}
}