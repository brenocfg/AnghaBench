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
typedef  int /*<<< orphan*/  u16 ;
struct zx_gpio {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int EINVAL ; 
 scalar_t__ ZX_GPIO_DIR ; 
 scalar_t__ ZX_GPIO_DO0 ; 
 scalar_t__ ZX_GPIO_DO1 ; 
 struct zx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  readw_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writew_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int zx_direction_output(struct gpio_chip *gc, unsigned offset,
		int value)
{
	struct zx_gpio *chip = gpiochip_get_data(gc);
	unsigned long flags;
	u16 gpiodir;

	if (offset >= gc->ngpio)
		return -EINVAL;

	raw_spin_lock_irqsave(&chip->lock, flags);
	gpiodir = readw_relaxed(chip->base + ZX_GPIO_DIR);
	gpiodir |= BIT(offset);
	writew_relaxed(gpiodir, chip->base + ZX_GPIO_DIR);

	if (value)
		writew_relaxed(BIT(offset), chip->base + ZX_GPIO_DO1);
	else
		writew_relaxed(BIT(offset), chip->base + ZX_GPIO_DO0);
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	return 0;
}