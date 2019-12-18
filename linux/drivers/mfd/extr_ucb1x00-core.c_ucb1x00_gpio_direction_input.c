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
struct ucb1x00 {int io_dir; int /*<<< orphan*/  io_lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_IO_DIR ; 
 struct ucb1x00* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ucb1x00_disable (struct ucb1x00*) ; 
 int /*<<< orphan*/  ucb1x00_enable (struct ucb1x00*) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (struct ucb1x00*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ucb1x00_gpio_direction_input(struct gpio_chip *chip, unsigned offset)
{
	struct ucb1x00 *ucb = gpiochip_get_data(chip);
	unsigned long flags;

	spin_lock_irqsave(&ucb->io_lock, flags);
	ucb->io_dir &= ~(1 << offset);
	ucb1x00_enable(ucb);
	ucb1x00_reg_write(ucb, UCB_IO_DIR, ucb->io_dir);
	ucb1x00_disable(ucb);
	spin_unlock_irqrestore(&ucb->io_lock, flags);

	return 0;
}