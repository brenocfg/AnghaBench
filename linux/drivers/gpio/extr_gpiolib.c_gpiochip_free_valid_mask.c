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
struct gpio_chip {int /*<<< orphan*/ * valid_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gpiochip_free_valid_mask(struct gpio_chip *gpiochip)
{
	bitmap_free(gpiochip->valid_mask);
	gpiochip->valid_mask = NULL;
}