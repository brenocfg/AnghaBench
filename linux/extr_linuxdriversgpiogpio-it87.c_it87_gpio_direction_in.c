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
typedef  int u8 ;
struct it87_gpio {int /*<<< orphan*/  lock; scalar_t__ output_base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct it87_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  superio_clear_mask (int,scalar_t__) ; 
 int superio_enter () ; 
 int /*<<< orphan*/  superio_exit () ; 

__attribute__((used)) static int it87_gpio_direction_in(struct gpio_chip *chip, unsigned gpio_num)
{
	u8 mask, group;
	int rc = 0;
	struct it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	group = (gpio_num / 8);

	spin_lock(&it87_gpio->lock);

	rc = superio_enter();
	if (rc)
		goto exit;

	/* clear the output enable bit */
	superio_clear_mask(mask, group + it87_gpio->output_base);

	superio_exit();

exit:
	spin_unlock(&it87_gpio->lock);
	return rc;
}