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
struct sh_pfc_pin {scalar_t__ enum_id; } ;
struct sh_pfc_gpio_pin {unsigned int dreg; unsigned int dbit; } ;
struct sh_pfc_chip {struct sh_pfc_gpio_pin* pins; struct sh_pfc* pfc; } ;
struct sh_pfc {TYPE_1__* info; } ;
struct pinmux_data_reg {int reg_width; scalar_t__* enum_ids; } ;
struct TYPE_2__ {struct pinmux_data_reg* data_regs; struct sh_pfc_pin* pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static void gpio_setup_data_reg(struct sh_pfc_chip *chip, unsigned idx)
{
	struct sh_pfc *pfc = chip->pfc;
	struct sh_pfc_gpio_pin *gpio_pin = &chip->pins[idx];
	const struct sh_pfc_pin *pin = &pfc->info->pins[idx];
	const struct pinmux_data_reg *dreg;
	unsigned int bit;
	unsigned int i;

	for (i = 0, dreg = pfc->info->data_regs; dreg->reg_width; ++i, ++dreg) {
		for (bit = 0; bit < dreg->reg_width; bit++) {
			if (dreg->enum_ids[bit] == pin->enum_id) {
				gpio_pin->dreg = i;
				gpio_pin->dbit = bit;
				return;
			}
		}
	}

	BUG();
}