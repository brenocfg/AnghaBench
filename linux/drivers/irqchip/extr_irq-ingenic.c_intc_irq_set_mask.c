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
typedef  int /*<<< orphan*/  uint32_t ;
struct irq_chip_regs {scalar_t__ disable; scalar_t__ enable; } ;
struct irq_chip_generic {scalar_t__ reg_base; TYPE_1__* chip_types; } ;
struct TYPE_2__ {struct irq_chip_regs regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void intc_irq_set_mask(struct irq_chip_generic *gc, uint32_t mask)
{
	struct irq_chip_regs *regs = &gc->chip_types->regs;

	writel(mask, gc->reg_base + regs->enable);
	writel(~mask, gc->reg_base + regs->disable);
}