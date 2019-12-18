#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sh_pfc_chip {TYPE_3__* regs; struct sh_pfc* pfc; } ;
struct sh_pfc {TYPE_2__* info; int /*<<< orphan*/  dev; } ;
struct pinmux_data_reg {scalar_t__ reg_width; } ;
struct TYPE_6__ {int /*<<< orphan*/  shadow; struct pinmux_data_reg const* info; } ;
struct TYPE_5__ {unsigned int nr_pins; TYPE_1__* pins; struct pinmux_data_reg* data_regs; } ;
struct TYPE_4__ {scalar_t__ enum_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_read_data_reg (struct sh_pfc_chip*,struct pinmux_data_reg const*) ; 
 int /*<<< orphan*/  gpio_setup_data_reg (struct sh_pfc_chip*,unsigned int) ; 

__attribute__((used)) static int gpio_setup_data_regs(struct sh_pfc_chip *chip)
{
	struct sh_pfc *pfc = chip->pfc;
	const struct pinmux_data_reg *dreg;
	unsigned int i;

	/* Count the number of data registers, allocate memory and initialize
	 * them.
	 */
	for (i = 0; pfc->info->data_regs[i].reg_width; ++i)
		;

	chip->regs = devm_kcalloc(pfc->dev, i, sizeof(*chip->regs),
				  GFP_KERNEL);
	if (chip->regs == NULL)
		return -ENOMEM;

	for (i = 0, dreg = pfc->info->data_regs; dreg->reg_width; ++i, ++dreg) {
		chip->regs[i].info = dreg;
		chip->regs[i].shadow = gpio_read_data_reg(chip, dreg);
	}

	for (i = 0; i < pfc->info->nr_pins; i++) {
		if (pfc->info->pins[i].enum_id == 0)
			continue;

		gpio_setup_data_reg(chip, i);
	}

	return 0;
}