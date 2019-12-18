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
struct gpio_mockup_chip {int /*<<< orphan*/  lock; TYPE_1__* lines; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_MOCKUP_DIR_OUT ; 
 int /*<<< orphan*/  __gpio_mockup_set (struct gpio_mockup_chip*,unsigned int,int) ; 
 struct gpio_mockup_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpio_mockup_dirout(struct gpio_chip *gc,
			      unsigned int offset, int value)
{
	struct gpio_mockup_chip *chip = gpiochip_get_data(gc);

	mutex_lock(&chip->lock);
	chip->lines[offset].dir = GPIO_MOCKUP_DIR_OUT;
	__gpio_mockup_set(chip, offset, value);
	mutex_unlock(&chip->lock);

	return 0;
}