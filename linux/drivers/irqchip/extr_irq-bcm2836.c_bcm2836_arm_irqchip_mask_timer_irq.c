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
struct irq_data {scalar_t__ hwirq; } ;

/* Variables and functions */
 scalar_t__ LOCAL_IRQ_CNTPSIRQ ; 
 int /*<<< orphan*/  LOCAL_TIMER_INT_CONTROL0 ; 
 int /*<<< orphan*/  bcm2836_arm_irqchip_mask_per_cpu_irq (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void bcm2836_arm_irqchip_mask_timer_irq(struct irq_data *d)
{
	bcm2836_arm_irqchip_mask_per_cpu_irq(LOCAL_TIMER_INT_CONTROL0,
					     d->hwirq - LOCAL_IRQ_CNTPSIRQ,
					     smp_processor_id());
}