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
struct pl061 {scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ GPIODIR ; 
 struct pl061* gpiochip_get_data (struct gpio_chip*) ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static int pl061_get_direction(struct gpio_chip *gc, unsigned offset)
{
	struct pl061 *pl061 = gpiochip_get_data(gc);

	return !(readb(pl061->base + GPIODIR) & BIT(offset));
}