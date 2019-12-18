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
struct mt6397_chip {int /*<<< orphan*/  regmap; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  handle_nested_irq (int) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void mt6397_irq_handle_reg(struct mt6397_chip *mt6397, int reg,
				  int irqbase)
{
	unsigned int status;
	int i, irq, ret;

	ret = regmap_read(mt6397->regmap, reg, &status);
	if (ret) {
		dev_err(mt6397->dev, "Failed to read irq status: %d\n", ret);
		return;
	}

	for (i = 0; i < 16; i++) {
		if (status & BIT(i)) {
			irq = irq_find_mapping(mt6397->irq_domain, irqbase + i);
			if (irq)
				handle_nested_irq(irq);
		}
	}

	regmap_write(mt6397->regmap, reg, status);
}