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
struct ucb1x00 {unsigned int io_out; unsigned int io_dir; int /*<<< orphan*/  io_lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_IO_DATA ; 
 int /*<<< orphan*/  UCB_IO_DIR ; 
 struct ucb1x00* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ucb1x00_disable (struct ucb1x00*) ; 
 int /*<<< orphan*/  ucb1x00_enable (struct ucb1x00*) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (struct ucb1x00*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ucb1x00_gpio_direction_output(struct gpio_chip *chip, unsigned offset
		, int value)
{
	struct ucb1x00 *ucb = gpiochip_get_data(chip);
	unsigned long flags;
	unsigned old, mask = 1 << offset;

	spin_lock_irqsave(&ucb->io_lock, flags);
	old = ucb->io_out;
	if (value)
		ucb->io_out |= mask;
	else
		ucb->io_out &= ~mask;

	ucb1x00_enable(ucb);
	if (old != ucb->io_out)
		ucb1x00_reg_write(ucb, UCB_IO_DATA, ucb->io_out);

	if (!(ucb->io_dir & mask)) {
		ucb->io_dir |= mask;
		ucb1x00_reg_write(ucb, UCB_IO_DIR, ucb->io_dir);
	}
	ucb1x00_disable(ucb);
	spin_unlock_irqrestore(&ucb->io_lock, flags);

	return 0;
}