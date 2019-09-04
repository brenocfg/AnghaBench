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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  enabled_mask; } ;
struct dpu_mdss {TYPE_1__ irq_controller; } ;

/* Variables and functions */
 struct dpu_mdss* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static void dpu_mdss_irq_unmask(struct irq_data *irqd)
{
	struct dpu_mdss *dpu_mdss = irq_data_get_irq_chip_data(irqd);

	/* memory barrier */
	smp_mb__before_atomic();
	set_bit(irqd->hwirq, &dpu_mdss->irq_controller.enabled_mask);
	/* memory barrier */
	smp_mb__after_atomic();
}