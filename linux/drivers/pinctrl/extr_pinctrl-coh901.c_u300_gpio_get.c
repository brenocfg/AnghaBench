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
struct u300_gpio {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int U300_PIN_BIT (unsigned int) ; 
 int /*<<< orphan*/  U300_PIN_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir ; 
 struct u300_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u300_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct u300_gpio *gpio = gpiochip_get_data(chip);

	return !!(readl(U300_PIN_REG(offset, dir)) & U300_PIN_BIT(offset));
}