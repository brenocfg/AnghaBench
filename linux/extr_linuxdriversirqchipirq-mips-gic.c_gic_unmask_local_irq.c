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
 int /*<<< orphan*/  BIT (int) ; 
 int GIC_HWIRQ_TO_LOCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_gic_vl_smask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gic_unmask_local_irq(struct irq_data *d)
{
	int intr = GIC_HWIRQ_TO_LOCAL(d->hwirq);

	write_gic_vl_smask(BIT(intr));
}