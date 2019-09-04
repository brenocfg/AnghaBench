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
struct adnp {int /*<<< orphan*/  i2c_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __adnp_gpio_set (struct adnp*,unsigned int,int) ; 
 struct adnp* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adnp_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct adnp *adnp = gpiochip_get_data(chip);

	mutex_lock(&adnp->i2c_lock);
	__adnp_gpio_set(adnp, offset, value);
	mutex_unlock(&adnp->i2c_lock);
}