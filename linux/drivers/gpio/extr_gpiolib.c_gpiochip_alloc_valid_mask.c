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
struct gpio_chip {int /*<<< orphan*/  valid_mask; scalar_t__ init_valid_mask; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  gpiochip_allocate_mask (struct gpio_chip*) ; 
 scalar_t__ of_gpio_need_valid_mask (struct gpio_chip*) ; 

__attribute__((used)) static int gpiochip_alloc_valid_mask(struct gpio_chip *gc)
{
	if (!(of_gpio_need_valid_mask(gc) || gc->init_valid_mask))
		return 0;

	gc->valid_mask = gpiochip_allocate_mask(gc);
	if (!gc->valid_mask)
		return -ENOMEM;

	return 0;
}