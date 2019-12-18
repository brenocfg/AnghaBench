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
struct vcpu_data {int pi_desc_addr; int /*<<< orphan*/  vector; } ;
struct irte {int p_pst; int pda_l; int pda_h; int /*<<< orphan*/  p_vector; scalar_t__ p_urgent; } ;
struct irq_data {struct intel_ir_data* chip_data; } ;
struct intel_ir_data {int /*<<< orphan*/  irq_2_iommu; struct irte irte_entry; } ;
typedef  int /*<<< orphan*/  irte_pi ;

/* Variables and functions */
 unsigned long PDA_HIGH_BIT ; 
 int PDA_LOW_BIT ; 
 int /*<<< orphan*/  dmar_copy_shared_irte (struct irte*,struct irte*) ; 
 int /*<<< orphan*/  memset (struct irte*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  modify_irte (int /*<<< orphan*/ *,struct irte*) ; 

__attribute__((used)) static int intel_ir_set_vcpu_affinity(struct irq_data *data, void *info)
{
	struct intel_ir_data *ir_data = data->chip_data;
	struct vcpu_data *vcpu_pi_info = info;

	/* stop posting interrupts, back to remapping mode */
	if (!vcpu_pi_info) {
		modify_irte(&ir_data->irq_2_iommu, &ir_data->irte_entry);
	} else {
		struct irte irte_pi;

		/*
		 * We are not caching the posted interrupt entry. We
		 * copy the data from the remapped entry and modify
		 * the fields which are relevant for posted mode. The
		 * cached remapped entry is used for switching back to
		 * remapped mode.
		 */
		memset(&irte_pi, 0, sizeof(irte_pi));
		dmar_copy_shared_irte(&irte_pi, &ir_data->irte_entry);

		/* Update the posted mode fields */
		irte_pi.p_pst = 1;
		irte_pi.p_urgent = 0;
		irte_pi.p_vector = vcpu_pi_info->vector;
		irte_pi.pda_l = (vcpu_pi_info->pi_desc_addr >>
				(32 - PDA_LOW_BIT)) & ~(-1UL << PDA_LOW_BIT);
		irte_pi.pda_h = (vcpu_pi_info->pi_desc_addr >> 32) &
				~(-1UL << PDA_HIGH_BIT);

		modify_irte(&ir_data->irq_2_iommu, &irte_pi);
	}

	return 0;
}