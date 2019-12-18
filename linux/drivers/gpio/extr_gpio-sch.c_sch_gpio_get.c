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
struct sch_gpio {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLV ; 
 struct sch_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int sch_gpio_reg_get (struct sch_gpio*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sch_gpio_get(struct gpio_chip *gc, unsigned gpio_num)
{
	struct sch_gpio *sch = gpiochip_get_data(gc);
	return sch_gpio_reg_get(sch, gpio_num, GLV);
}