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
typedef  int /*<<< orphan*/  u32 ;
struct xgene_gpio {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 unsigned long GPIO_BANK_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  GPIO_BIT_OFFSET (unsigned int) ; 
 unsigned long GPIO_SET_DR_OFFSET ; 
 struct xgene_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int xgene_gpio_dir_in(struct gpio_chip *gc, unsigned int offset)
{
	struct xgene_gpio *chip = gpiochip_get_data(gc);
	unsigned long flags, bank_offset;
	u32 dirval, bit_offset;

	bank_offset = GPIO_SET_DR_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset);

	spin_lock_irqsave(&chip->lock, flags);

	dirval = ioread32(chip->base + bank_offset);
	dirval |= BIT(bit_offset);
	iowrite32(dirval, chip->base + bank_offset);

	spin_unlock_irqrestore(&chip->lock, flags);

	return 0;
}