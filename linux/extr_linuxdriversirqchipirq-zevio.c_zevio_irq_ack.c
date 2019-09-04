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
struct irq_data {int dummy; } ;
struct irq_chip_regs {scalar_t__ ack; } ;
struct irq_chip_generic {scalar_t__ reg_base; } ;
struct TYPE_2__ {struct irq_chip_regs regs; } ;

/* Variables and functions */
 TYPE_1__* irq_data_get_chip_type (struct irq_data*) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void zevio_irq_ack(struct irq_data *irqd)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(irqd);
	struct irq_chip_regs *regs = &irq_data_get_chip_type(irqd)->regs;

	readl(gc->reg_base + regs->ack);
}