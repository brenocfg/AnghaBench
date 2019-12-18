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
struct pm_irq_chip {int /*<<< orphan*/  irqdomain; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int pm8xxx_read_block_irq (struct pm_irq_chip*,int,unsigned int*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static int pm8xxx_irq_block_handler(struct pm_irq_chip *chip, int block)
{
	int pmirq, irq, i, ret = 0;
	unsigned int bits;

	ret = pm8xxx_read_block_irq(chip, block, &bits);
	if (ret) {
		pr_err("Failed reading %d block ret=%d", block, ret);
		return ret;
	}
	if (!bits) {
		pr_err("block bit set in master but no irqs: %d", block);
		return 0;
	}

	/* Check IRQ bits */
	for (i = 0; i < 8; i++) {
		if (bits & (1 << i)) {
			pmirq = block * 8 + i;
			irq = irq_find_mapping(chip->irqdomain, pmirq);
			generic_handle_irq(irq);
		}
	}
	return 0;
}