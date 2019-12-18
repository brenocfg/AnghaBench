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
struct TYPE_2__ {int /*<<< orphan*/  dir; int /*<<< orphan*/  wdata; } ;
struct plgpio {unsigned int (* p2o ) (unsigned int) ;int p2o_regs; int /*<<< orphan*/  lock; TYPE_1__ regs; int /*<<< orphan*/  base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PTO_DIR_REG ; 
 int PTO_WDATA_REG ; 
 struct plgpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  plgpio_reg_reset (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plgpio_reg_set (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int stub1 (unsigned int) ; 

__attribute__((used)) static int plgpio_direction_output(struct gpio_chip *chip, unsigned offset,
		int value)
{
	struct plgpio *plgpio = gpiochip_get_data(chip);
	unsigned long flags;
	unsigned dir_offset = offset, wdata_offset = offset, tmp;

	/* get correct offset for "offset" pin */
	if (plgpio->p2o && (plgpio->p2o_regs & (PTO_DIR_REG | PTO_WDATA_REG))) {
		tmp = plgpio->p2o(offset);
		if (tmp == -1)
			return -EINVAL;

		if (plgpio->p2o_regs & PTO_DIR_REG)
			dir_offset = tmp;
		if (plgpio->p2o_regs & PTO_WDATA_REG)
			wdata_offset = tmp;
	}

	spin_lock_irqsave(&plgpio->lock, flags);
	if (value)
		plgpio_reg_set(plgpio->base, wdata_offset,
				plgpio->regs.wdata);
	else
		plgpio_reg_reset(plgpio->base, wdata_offset,
				plgpio->regs.wdata);

	plgpio_reg_reset(plgpio->base, dir_offset, plgpio->regs.dir);
	spin_unlock_irqrestore(&plgpio->lock, flags);

	return 0;
}