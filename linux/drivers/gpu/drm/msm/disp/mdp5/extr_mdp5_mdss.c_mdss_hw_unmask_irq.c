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
struct TYPE_2__ {int /*<<< orphan*/  enabled_mask; } ;
struct mdp5_mdss {TYPE_1__ irqcontroller; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 struct mdp5_mdss* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static void mdss_hw_unmask_irq(struct irq_data *irqd)
{
	struct mdp5_mdss *mdp5_mdss = irq_data_get_irq_chip_data(irqd);

	smp_mb__before_atomic();
	set_bit(irqd->hwirq, &mdp5_mdss->irqcontroller.enabled_mask);
	smp_mb__after_atomic();
}