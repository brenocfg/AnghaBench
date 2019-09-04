#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int base; } ;
struct samsung_gpio_chip {TYPE_1__ chip; } ;

/* Variables and functions */
 unsigned int samsung_gpio_do_getcfg (struct samsung_gpio_chip*,int) ; 
 int /*<<< orphan*/  samsung_gpio_lock (struct samsung_gpio_chip*,unsigned long) ; 
 int /*<<< orphan*/  samsung_gpio_unlock (struct samsung_gpio_chip*,unsigned long) ; 
 struct samsung_gpio_chip* samsung_gpiolib_getchip (unsigned int) ; 

unsigned s3c_gpio_getcfg(unsigned int pin)
{
	struct samsung_gpio_chip *chip = samsung_gpiolib_getchip(pin);
	unsigned long flags;
	unsigned ret = 0;
	int offset;

	if (chip) {
		offset = pin - chip->chip.base;

		samsung_gpio_lock(chip, flags);
		ret = samsung_gpio_do_getcfg(chip, offset);
		samsung_gpio_unlock(chip, flags);
	}

	return ret;
}