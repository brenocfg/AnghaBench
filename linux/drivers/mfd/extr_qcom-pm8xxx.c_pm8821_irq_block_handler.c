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
struct pm_irq_chip {int /*<<< orphan*/  irqdomain; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int PM8821_BLOCKS_PER_MASTER ; 
 int /*<<< orphan*/  PM8821_SSBI_ADDR_IRQ_ROOT (int,int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void pm8821_irq_block_handler(struct pm_irq_chip *chip,
				     int master, int block)
{
	int pmirq, irq, i, ret;
	unsigned int bits;

	ret = regmap_read(chip->regmap,
			  PM8821_SSBI_ADDR_IRQ_ROOT(master, block), &bits);
	if (ret) {
		pr_err("Reading block %d failed ret=%d", block, ret);
		return;
	}

	/* Convert block offset to global block number */
	block += (master * PM8821_BLOCKS_PER_MASTER) - 1;

	/* Check IRQ bits */
	for (i = 0; i < 8; i++) {
		if (bits & BIT(i)) {
			pmirq = block * 8 + i;
			irq = irq_find_mapping(chip->irqdomain, pmirq);
			generic_handle_irq(irq);
		}
	}
}