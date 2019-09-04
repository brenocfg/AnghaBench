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
typedef  int u8 ;
struct gpio_chip {int dummy; } ;
struct ad5592r_state {int gpio_out; int gpio_val; int /*<<< orphan*/  gpio_lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* gpio_read ) (struct ad5592r_state*,int*) ;} ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 struct ad5592r_state* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ad5592r_state*,int*) ; 

__attribute__((used)) static int ad5592r_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct ad5592r_state *st = gpiochip_get_data(chip);
	int ret = 0;
	u8 val;

	mutex_lock(&st->gpio_lock);

	if (st->gpio_out & BIT(offset))
		val = st->gpio_val;
	else
		ret = st->ops->gpio_read(st, &val);

	mutex_unlock(&st->gpio_lock);

	if (ret < 0)
		return ret;

	return !!(val & BIT(offset));
}