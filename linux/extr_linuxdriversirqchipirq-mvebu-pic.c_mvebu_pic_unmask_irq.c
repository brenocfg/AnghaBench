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
struct mvebu_pic {scalar_t__ base; } ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 scalar_t__ PIC_MASK ; 
 struct mvebu_pic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mvebu_pic_unmask_irq(struct irq_data *d)
{
	struct mvebu_pic *pic = irq_data_get_irq_chip_data(d);
	u32 reg;

	reg = readl(pic->base + PIC_MASK);
	reg &= ~(1 << d->hwirq);
	writel(reg, pic->base + PIC_MASK);
}