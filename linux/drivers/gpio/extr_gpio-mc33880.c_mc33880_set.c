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
struct mc33880 {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mc33880_set (struct mc33880*,unsigned int,int) ; 
 struct mc33880* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mc33880_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct mc33880 *mc = gpiochip_get_data(chip);

	mutex_lock(&mc->lock);

	__mc33880_set(mc, offset, value);

	mutex_unlock(&mc->lock);
}