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
struct intel_iommu {int /*<<< orphan*/  name; int /*<<< orphan*/  reg_phys; int /*<<< orphan*/  ecap; } ;
struct dmar_drhd_unit {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ecap_eim_support (int /*<<< orphan*/ ) ; 
 int intel_setup_irq_remapping (struct intel_iommu*) ; 
 int /*<<< orphan*/  intel_teardown_irq_remapping (struct intel_iommu*) ; 
 int /*<<< orphan*/  iommu_enable_irq_remapping (struct intel_iommu*) ; 
 scalar_t__ ir_parse_ioapic_hpet_scope (int /*<<< orphan*/ ,struct intel_iommu*) ; 
 int /*<<< orphan*/  ir_remove_ioapic_hpet_scope (struct intel_iommu*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int x2apic_enabled () ; 

__attribute__((used)) static int dmar_ir_add(struct dmar_drhd_unit *dmaru, struct intel_iommu *iommu)
{
	int ret;
	int eim = x2apic_enabled();

	if (eim && !ecap_eim_support(iommu->ecap)) {
		pr_info("DRHD %Lx: EIM not supported by DRHD, ecap %Lx\n",
			iommu->reg_phys, iommu->ecap);
		return -ENODEV;
	}

	if (ir_parse_ioapic_hpet_scope(dmaru->hdr, iommu)) {
		pr_warn("DRHD %Lx: failed to parse managed IOAPIC/HPET\n",
			iommu->reg_phys);
		return -ENODEV;
	}

	/* TODO: check all IOAPICs are covered by IOMMU */

	/* Setup Interrupt-remapping now. */
	ret = intel_setup_irq_remapping(iommu);
	if (ret) {
		pr_err("Failed to setup irq remapping for %s\n",
		       iommu->name);
		intel_teardown_irq_remapping(iommu);
		ir_remove_ioapic_hpet_scope(iommu);
	} else {
		iommu_enable_irq_remapping(iommu);
	}

	return ret;
}