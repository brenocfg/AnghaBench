#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct vx855_gpio {int /*<<< orphan*/  lock; int /*<<< orphan*/  io_gpo; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NR_VX855_GPI ; 
 unsigned int NR_VX855_GPInO ; 
 int /*<<< orphan*/  gpio_o_bit (unsigned int) ; 
 struct vx855_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int vx855gpio_direction_input(struct gpio_chip *gpio,
				     unsigned int nr)
{
	struct vx855_gpio *vg = gpiochip_get_data(gpio);
	unsigned long flags;
	u_int32_t reg_out;

	/* Real GPI bits are always in input direction */
	if (nr < NR_VX855_GPI)
		return 0;

	/* Real GPO bits cannot be put in output direction */
	if (nr < NR_VX855_GPInO)
		return -EINVAL;

	/* Open Drain GPIO have to be set to one */
	spin_lock_irqsave(&vg->lock, flags);
	reg_out = inl(vg->io_gpo);
	reg_out |= gpio_o_bit(nr - NR_VX855_GPInO);
	outl(reg_out, vg->io_gpo);
	spin_unlock_irqrestore(&vg->lock, flags);

	return 0;
}