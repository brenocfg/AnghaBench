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
struct gpio_reg {int direction; } ;
struct gpio_chip {int /*<<< orphan*/  (* set ) (struct gpio_chip*,unsigned int,int) ;} ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  stub1 (struct gpio_chip*,unsigned int,int) ; 
 struct gpio_reg* to_gpio_reg (struct gpio_chip*) ; 

__attribute__((used)) static int gpio_reg_direction_output(struct gpio_chip *gc, unsigned offset,
	int value)
{
	struct gpio_reg *r = to_gpio_reg(gc);

	if (r->direction & BIT(offset))
		return -ENOTSUPP;

	gc->set(gc, offset, value);
	return 0;
}