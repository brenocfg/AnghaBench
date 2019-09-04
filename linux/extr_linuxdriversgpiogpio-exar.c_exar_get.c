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
struct exar_gpio_chip {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 struct exar_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static int exar_get(struct gpio_chip *chip, unsigned int reg)
{
	struct exar_gpio_chip *exar_gpio = gpiochip_get_data(chip);
	int value;

	mutex_lock(&exar_gpio->lock);
	value = readb(exar_gpio->regs + reg);
	mutex_unlock(&exar_gpio->lock);

	return value;
}