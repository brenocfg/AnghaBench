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
struct pisosr_gpio {scalar_t__* buffer; } ;
struct gpio_chip {int /*<<< orphan*/  ngpio; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int /*<<< orphan*/ ) ; 
 struct pisosr_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pisosr_gpio_refresh (struct pisosr_gpio*) ; 

__attribute__((used)) static int pisosr_gpio_get_multiple(struct gpio_chip *chip,
				    unsigned long *mask, unsigned long *bits)
{
	struct pisosr_gpio *gpio = gpiochip_get_data(chip);
	unsigned int nbytes = DIV_ROUND_UP(chip->ngpio, 8);
	unsigned int i, j;

	pisosr_gpio_refresh(gpio);

	bitmap_zero(bits, chip->ngpio);
	for (i = 0; i < nbytes; i++) {
		j = i / sizeof(unsigned long);
		bits[j] |= ((unsigned long) gpio->buffer[i])
			   << (8 * (i % sizeof(unsigned long)));
	}

	return 0;
}