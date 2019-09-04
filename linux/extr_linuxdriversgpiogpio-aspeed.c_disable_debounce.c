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
struct gpio_chip {int dummy; } ;
struct aspeed_gpio {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  configure_timer (struct aspeed_gpio*,unsigned int,int /*<<< orphan*/ ) ; 
 struct aspeed_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int unregister_allocated_timer (struct aspeed_gpio*,unsigned int) ; 

__attribute__((used)) static int disable_debounce(struct gpio_chip *chip, unsigned int offset)
{
	struct aspeed_gpio *gpio = gpiochip_get_data(chip);
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&gpio->lock, flags);

	rc = unregister_allocated_timer(gpio, offset);
	if (!rc)
		configure_timer(gpio, offset, 0);

	spin_unlock_irqrestore(&gpio->lock, flags);

	return rc;
}