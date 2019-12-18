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
struct gpio_chip {int dummy; } ;
struct dc_pinmap {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int GP_DRIVE0 (unsigned int) ; 
 unsigned int PINS_PER_COLLECTION ; 
 int /*<<< orphan*/  dc_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 struct dc_pinmap* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  readb_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dc_gpio_direction_output(struct gpio_chip *chip, unsigned gpio,
				    int value)
{
	struct dc_pinmap *pmap = gpiochip_get_data(chip);
	int reg_off = GP_DRIVE0(gpio/PINS_PER_COLLECTION);
	int bit_off = gpio % PINS_PER_COLLECTION;
	u8 drive;
	unsigned long flags;

	dc_gpio_set(chip, gpio, value);

	spin_lock_irqsave(&pmap->lock, flags);
	drive = readb_relaxed(pmap->regs + reg_off);
	drive |= BIT(bit_off);
	writeb_relaxed(drive, pmap->regs + reg_off);
	spin_unlock_irqrestore(&pmap->lock, flags);

	return 0;
}