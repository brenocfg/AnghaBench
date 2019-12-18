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
typedef  int /*<<< orphan*/  u32 ;
struct irqsteer_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  reg_num; scalar_t__ regs; } ;
struct irq_data {int hwirq; struct irqsteer_data* chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ CHANMASK (int,int /*<<< orphan*/ ) ; 
 int imx_irqsteer_get_reg_index (struct irqsteer_data*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void imx_irqsteer_irq_unmask(struct irq_data *d)
{
	struct irqsteer_data *data = d->chip_data;
	int idx = imx_irqsteer_get_reg_index(data, d->hwirq);
	unsigned long flags;
	u32 val;

	raw_spin_lock_irqsave(&data->lock, flags);
	val = readl_relaxed(data->regs + CHANMASK(idx, data->reg_num));
	val |= BIT(d->hwirq % 32);
	writel_relaxed(val, data->regs + CHANMASK(idx, data->reg_num));
	raw_spin_unlock_irqrestore(&data->lock, flags);
}