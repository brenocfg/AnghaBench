#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct max8998_dev {int* irq_masks_cur; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int reg; int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MAX8998_IRQ_NR ; 
 int MAX8998_NUM_IRQ_REGS ; 
 int /*<<< orphan*/  MAX8998_REG_IRQ1 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_nested_irq (int) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int max8998_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 TYPE_1__* max8998_irqs ; 

__attribute__((used)) static irqreturn_t max8998_irq_thread(int irq, void *data)
{
	struct max8998_dev *max8998 = data;
	u8 irq_reg[MAX8998_NUM_IRQ_REGS];
	int ret;
	int i;

	ret = max8998_bulk_read(max8998->i2c, MAX8998_REG_IRQ1,
			MAX8998_NUM_IRQ_REGS, irq_reg);
	if (ret < 0) {
		dev_err(max8998->dev, "Failed to read interrupt register: %d\n",
				ret);
		return IRQ_NONE;
	}

	/* Apply masking */
	for (i = 0; i < MAX8998_NUM_IRQ_REGS; i++)
		irq_reg[i] &= ~max8998->irq_masks_cur[i];

	/* Report */
	for (i = 0; i < MAX8998_IRQ_NR; i++) {
		if (irq_reg[max8998_irqs[i].reg - 1] & max8998_irqs[i].mask) {
			irq = irq_find_mapping(max8998->irq_domain, i);
			if (WARN_ON(!irq)) {
				disable_irq_nosync(max8998->irq);
				return IRQ_NONE;
			}
			handle_nested_irq(irq);
		}
	}

	return IRQ_HANDLED;
}