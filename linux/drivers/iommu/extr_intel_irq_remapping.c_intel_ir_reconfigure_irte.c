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
struct irte {int /*<<< orphan*/  dest_id; int /*<<< orphan*/  vector; } ;
struct irq_data {struct intel_ir_data* chip_data; } ;
struct irq_cfg {int /*<<< orphan*/  dest_apicid; int /*<<< orphan*/  vector; } ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct intel_ir_data {TYPE_1__ irq_2_iommu; struct irte irte_entry; } ;

/* Variables and functions */
 scalar_t__ IRQ_REMAPPING ; 
 int /*<<< orphan*/  IRTE_DEST (int /*<<< orphan*/ ) ; 
 struct irq_cfg* irqd_cfg (struct irq_data*) ; 
 int /*<<< orphan*/  modify_irte (TYPE_1__*,struct irte*) ; 

__attribute__((used)) static void intel_ir_reconfigure_irte(struct irq_data *irqd, bool force)
{
	struct intel_ir_data *ir_data = irqd->chip_data;
	struct irte *irte = &ir_data->irte_entry;
	struct irq_cfg *cfg = irqd_cfg(irqd);

	/*
	 * Atomically updates the IRTE with the new destination, vector
	 * and flushes the interrupt entry cache.
	 */
	irte->vector = cfg->vector;
	irte->dest_id = IRTE_DEST(cfg->dest_apicid);

	/* Update the hardware only if the interrupt is in remapped mode. */
	if (force || ir_data->irq_2_iommu.mode == IRQ_REMAPPING)
		modify_irte(&ir_data->irq_2_iommu, irte);
}