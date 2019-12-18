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
struct gic_all_vpes_chip_data {scalar_t__ mask; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int GIC_HWIRQ_TO_LOCAL (int /*<<< orphan*/ ) ; 
 struct gic_all_vpes_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mips_gic_vx_map_reg (unsigned int) ; 
 int /*<<< orphan*/  write_gic_vl_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_gic_vl_smask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gic_all_vpes_irq_cpu_online(struct irq_data *d)
{
	struct gic_all_vpes_chip_data *cd;
	unsigned int intr;

	intr = GIC_HWIRQ_TO_LOCAL(d->hwirq);
	cd = irq_data_get_irq_chip_data(d);

	write_gic_vl_map(mips_gic_vx_map_reg(intr), cd->map);
	if (cd->mask)
		write_gic_vl_smask(BIT(intr));
}