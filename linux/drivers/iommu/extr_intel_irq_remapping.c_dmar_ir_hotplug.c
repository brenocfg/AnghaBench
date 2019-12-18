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
struct intel_iommu {TYPE_1__* ir_table; int /*<<< orphan*/  cap; int /*<<< orphan*/  ecap; } ;
struct dmar_drhd_unit {struct intel_iommu* iommu; } ;
struct TYPE_2__ {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  INTR_REMAP_TABLE_ENTRIES ; 
 int /*<<< orphan*/  IRQ_POSTING_CAP ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_pi_support (int /*<<< orphan*/ ) ; 
 int dmar_ir_add (struct dmar_drhd_unit*,struct intel_iommu*) ; 
 int /*<<< orphan*/  ecap_ir_support (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_teardown_irq_remapping (struct intel_iommu*) ; 
 int /*<<< orphan*/  iommu_disable_irq_remapping (struct intel_iommu*) ; 
 int /*<<< orphan*/  ir_remove_ioapic_hpet_scope (struct intel_iommu*) ; 
 scalar_t__ irq_remapping_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_remapping_enabled ; 

int dmar_ir_hotplug(struct dmar_drhd_unit *dmaru, bool insert)
{
	int ret = 0;
	struct intel_iommu *iommu = dmaru->iommu;

	if (!irq_remapping_enabled)
		return 0;
	if (iommu == NULL)
		return -EINVAL;
	if (!ecap_ir_support(iommu->ecap))
		return 0;
	if (irq_remapping_cap(IRQ_POSTING_CAP) &&
	    !cap_pi_support(iommu->cap))
		return -EBUSY;

	if (insert) {
		if (!iommu->ir_table)
			ret = dmar_ir_add(dmaru, iommu);
	} else {
		if (iommu->ir_table) {
			if (!bitmap_empty(iommu->ir_table->bitmap,
					  INTR_REMAP_TABLE_ENTRIES)) {
				ret = -EBUSY;
			} else {
				iommu_disable_irq_remapping(iommu);
				intel_teardown_irq_remapping(iommu);
				ir_remove_ioapic_hpet_scope(iommu);
			}
		}
	}

	return ret;
}