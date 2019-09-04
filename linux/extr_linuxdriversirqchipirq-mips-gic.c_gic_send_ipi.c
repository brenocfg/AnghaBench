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
struct irq_data {int dummy; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int GIC_HWIRQ_TO_SHARED (int /*<<< orphan*/ ) ; 
 int GIC_WEDGE_RW ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  write_gic_wedge (int) ; 

__attribute__((used)) static void gic_send_ipi(struct irq_data *d, unsigned int cpu)
{
	irq_hw_number_t hwirq = GIC_HWIRQ_TO_SHARED(irqd_to_hwirq(d));

	write_gic_wedge(GIC_WEDGE_RW | hwirq);
}