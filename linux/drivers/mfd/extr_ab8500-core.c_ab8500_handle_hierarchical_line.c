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
typedef  int u8 ;
struct ab8500 {int mask_size; int* irq_reg_offset; int* mask; int /*<<< orphan*/  domain; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AB8500_INT_GPIO41F ; 
 int AB8500_INT_GPIO6F ; 
 int AB8540_INT_GPIO43F ; 
 int AB8540_INT_GPIO44F ; 
 int AB9540_INT_GPIO50F ; 
 int AB9540_INT_GPIO54F ; 
 int ENXIO ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  handle_nested_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ab8500_handle_hierarchical_line(struct ab8500 *ab8500,
					int latch_offset, u8 latch_val)
{
	int int_bit, line, i;

	for (i = 0; i < ab8500->mask_size; i++)
		if (ab8500->irq_reg_offset[i] == latch_offset)
			break;

	if (i >= ab8500->mask_size) {
		dev_err(ab8500->dev, "Register offset 0x%2x not declared\n",
				latch_offset);
		return -ENXIO;
	}

	/* ignore masked out interrupts */
	latch_val &= ~ab8500->mask[i];

	while (latch_val) {
		int_bit = __ffs(latch_val);
		line = (i << 3) + int_bit;
		latch_val &= ~(1 << int_bit);

		/*
		 * This handles the falling edge hwirqs from the GPIO
		 * lines. Route them back to the line registered for the
		 * rising IRQ, as this is merely a flag for the same IRQ
		 * in linux terms.
		 */
		if (line >= AB8500_INT_GPIO6F && line <= AB8500_INT_GPIO41F)
			line -= 16;
		if (line >= AB9540_INT_GPIO50F && line <= AB9540_INT_GPIO54F)
			line -= 8;
		if (line == AB8540_INT_GPIO43F || line == AB8540_INT_GPIO44F)
			line += 1;

		handle_nested_irq(irq_create_mapping(ab8500->domain, line));
	}

	return 0;
}