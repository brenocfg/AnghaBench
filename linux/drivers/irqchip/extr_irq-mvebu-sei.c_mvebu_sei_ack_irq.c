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
struct mvebu_sei {scalar_t__ base; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ GICP_SECR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEI_IRQ_REG_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEI_IRQ_REG_IDX (int /*<<< orphan*/ ) ; 
 struct mvebu_sei* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvebu_sei_ack_irq(struct irq_data *d)
{
	struct mvebu_sei *sei = irq_data_get_irq_chip_data(d);
	u32 reg_idx = SEI_IRQ_REG_IDX(d->hwirq);

	writel_relaxed(BIT(SEI_IRQ_REG_BIT(d->hwirq)),
		       sei->base + GICP_SECR(reg_idx));
}