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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct intel_iommu {int dummy; } ;

/* Variables and functions */
 int INTR_REMAP ; 
 int /*<<< orphan*/  PCI_FUNC (int) ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 char* dmar_get_fault_reason (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int dmar_fault_do_one(struct intel_iommu *iommu, int type,
		u8 fault_reason, int pasid, u16 source_id,
		unsigned long long addr)
{
	const char *reason;
	int fault_type;

	reason = dmar_get_fault_reason(fault_reason, &fault_type);

	if (fault_type == INTR_REMAP)
		pr_err("[INTR-REMAP] Request device [%02x:%02x.%d] fault index %llx [fault reason %02d] %s\n",
			source_id >> 8, PCI_SLOT(source_id & 0xFF),
			PCI_FUNC(source_id & 0xFF), addr >> 48,
			fault_reason, reason);
	else
		pr_err("[%s] Request device [%02x:%02x.%d] PASID %x fault addr %llx [fault reason %02d] %s\n",
		       type ? "DMA Read" : "DMA Write",
		       source_id >> 8, PCI_SLOT(source_id & 0xFF),
		       PCI_FUNC(source_id & 0xFF), pasid, addr,
		       fault_reason, reason);
	return 0;
}