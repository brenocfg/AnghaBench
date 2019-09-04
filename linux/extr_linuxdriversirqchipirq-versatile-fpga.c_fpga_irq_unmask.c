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
typedef  int u32 ;
struct irq_data {int hwirq; } ;
struct fpga_irq_data {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IRQ_ENABLE_SET ; 
 struct fpga_irq_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void fpga_irq_unmask(struct irq_data *d)
{
	struct fpga_irq_data *f = irq_data_get_irq_chip_data(d);
	u32 mask = 1 << d->hwirq;

	writel(mask, f->base + IRQ_ENABLE_SET);
}