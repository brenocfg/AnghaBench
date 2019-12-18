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
struct mpc8xxx_gpio_chip {int (* direction_output ) (struct gpio_chip*,unsigned int,int) ;} ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mpc8xxx_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int stub1 (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int mpc5125_gpio_dir_out(struct gpio_chip *gc,
				unsigned int gpio, int val)
{
	struct mpc8xxx_gpio_chip *mpc8xxx_gc = gpiochip_get_data(gc);
	/* GPIO 0..3 are input only on MPC5125 */
	if (gpio <= 3)
		return -EINVAL;

	return mpc8xxx_gc->direction_output(gc, gpio, val);
}