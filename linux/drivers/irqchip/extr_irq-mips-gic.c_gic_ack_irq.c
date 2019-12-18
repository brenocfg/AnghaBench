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
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 unsigned int GIC_HWIRQ_TO_SHARED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_gic_wedge (unsigned int) ; 

__attribute__((used)) static void gic_ack_irq(struct irq_data *d)
{
	unsigned int irq = GIC_HWIRQ_TO_SHARED(d->hwirq);

	write_gic_wedge(irq);
}