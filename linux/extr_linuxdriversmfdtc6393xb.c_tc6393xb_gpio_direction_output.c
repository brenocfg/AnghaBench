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
typedef  int /*<<< orphan*/  u8 ;
struct tc6393xb {int /*<<< orphan*/  lock; scalar_t__ scr; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCR_GPO_DOECR (unsigned int) ; 
 int /*<<< orphan*/  TC_GPIO_BIT (unsigned int) ; 
 int /*<<< orphan*/  __tc6393xb_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 struct tc6393xb* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmio_ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tc6393xb_gpio_direction_output(struct gpio_chip *chip,
			unsigned offset, int value)
{
	struct tc6393xb *tc6393xb = gpiochip_get_data(chip);
	unsigned long flags;
	u8 doecr;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	__tc6393xb_gpio_set(chip, offset, value);

	doecr = tmio_ioread8(tc6393xb->scr + SCR_GPO_DOECR(offset / 8));
	doecr |= TC_GPIO_BIT(offset);
	tmio_iowrite8(doecr, tc6393xb->scr + SCR_GPO_DOECR(offset / 8));

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	return 0;
}