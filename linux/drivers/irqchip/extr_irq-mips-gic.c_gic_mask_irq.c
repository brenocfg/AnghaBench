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
 int /*<<< orphan*/  gic_clear_pcpu_masks (unsigned int) ; 
 int /*<<< orphan*/  write_gic_rmask (unsigned int) ; 

__attribute__((used)) static void gic_mask_irq(struct irq_data *d)
{
	unsigned int intr = GIC_HWIRQ_TO_SHARED(d->hwirq);

	write_gic_rmask(intr);
	gic_clear_pcpu_masks(intr);
}