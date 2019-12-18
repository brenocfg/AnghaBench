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
struct gpio_chip {int (* init_valid_mask ) (struct gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ngpio; int /*<<< orphan*/  valid_mask; } ;

/* Variables and functions */
 int stub1 (struct gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpiochip_init_valid_mask(struct gpio_chip *gc)
{
	if (gc->init_valid_mask)
		return gc->init_valid_mask(gc,
					   gc->valid_mask,
					   gc->ngpio);

	return 0;
}