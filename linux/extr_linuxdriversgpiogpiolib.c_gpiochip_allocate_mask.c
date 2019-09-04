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
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_fill (unsigned long*,int /*<<< orphan*/ ) ; 
 unsigned long* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long *gpiochip_allocate_mask(struct gpio_chip *chip)
{
	unsigned long *p;

	p = kmalloc_array(BITS_TO_LONGS(chip->ngpio), sizeof(*p), GFP_KERNEL);
	if (!p)
		return NULL;

	/* Assume by default all GPIOs are valid */
	bitmap_fill(p, chip->ngpio);

	return p;
}