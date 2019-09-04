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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  LOONGSON_GPIOIE ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loongson_gpio_direction_input(struct gpio_chip *chip, unsigned gpio)
{
	u32 temp;

	spin_lock(&gpio_lock);
	temp = LOONGSON_GPIOIE;
	temp |= BIT(gpio);
	LOONGSON_GPIOIE = temp;
	spin_unlock(&gpio_lock);

	return 0;
}