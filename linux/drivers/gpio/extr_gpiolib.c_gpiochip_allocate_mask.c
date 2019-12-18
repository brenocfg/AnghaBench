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
struct gpio_chip {int /*<<< orphan*/  ngpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long* bitmap_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_fill (unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long *gpiochip_allocate_mask(struct gpio_chip *chip)
{
	unsigned long *p;

	p = bitmap_alloc(chip->ngpio, GFP_KERNEL);
	if (!p)
		return NULL;

	/* Assume by default all GPIOs are valid */
	bitmap_fill(p, chip->ngpio);

	return p;
}