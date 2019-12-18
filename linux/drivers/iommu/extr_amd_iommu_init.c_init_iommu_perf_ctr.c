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
typedef  void* u8 ;
typedef  int u64 ;
struct pci_dev {int dummy; } ;
struct amd_iommu {void* max_counters; void* max_banks; scalar_t__ mmio_base; struct pci_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEATURE_PC ; 
 scalar_t__ MMIO_CNTR_CONF_OFFSET ; 
 int amd_iommu_pc_present ; 
 int /*<<< orphan*/  iommu_feature (struct amd_iommu*,int /*<<< orphan*/ ) ; 
 scalar_t__ iommu_pc_get_set_reg (struct amd_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void init_iommu_perf_ctr(struct amd_iommu *iommu)
{
	struct pci_dev *pdev = iommu->dev;
	u64 val = 0xabcd, val2 = 0;

	if (!iommu_feature(iommu, FEATURE_PC))
		return;

	amd_iommu_pc_present = true;

	/* Check if the performance counters can be written to */
	if ((iommu_pc_get_set_reg(iommu, 0, 0, 0, &val, true)) ||
	    (iommu_pc_get_set_reg(iommu, 0, 0, 0, &val2, false)) ||
	    (val != val2)) {
		pci_err(pdev, "Unable to write to IOMMU perf counter.\n");
		amd_iommu_pc_present = false;
		return;
	}

	pci_info(pdev, "IOMMU performance counters supported\n");

	val = readl(iommu->mmio_base + MMIO_CNTR_CONF_OFFSET);
	iommu->max_banks = (u8) ((val >> 12) & 0x3f);
	iommu->max_counters = (u8) ((val >> 7) & 0xf);
}