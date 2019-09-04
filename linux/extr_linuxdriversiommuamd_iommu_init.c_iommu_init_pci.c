#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct amd_iommu {int cap_ptr; int devid; int cap; int features; int is_iommu_v2; int stored_addr_lo; int stored_addr_hi; TYPE_2__* dev; int /*<<< orphan*/  iommu; int /*<<< orphan*/  index; int /*<<< orphan*/ * stored_l2; int /*<<< orphan*/ ** stored_l1; void* root_pdev; scalar_t__ mmio_base; } ;
struct TYPE_6__ {int match_driver; int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FEATURE_GLXVAL_MASK ; 
 int FEATURE_GLXVAL_SHIFT ; 
 int /*<<< orphan*/  FEATURE_GT ; 
 int FEATURE_PASID_MASK ; 
 int FEATURE_PASID_SHIFT ; 
 int /*<<< orphan*/  FEATURE_PPR ; 
 int IOMMU_CAP_IOTLB ; 
 unsigned long IOMMU_CAP_NPCACHE ; 
 int MMIO_CAP_HDR_OFFSET ; 
 scalar_t__ MMIO_EXT_FEATURES ; 
 int MMIO_MISC_OFFSET ; 
 int MMIO_RANGE_OFFSET ; 
 int PASID_MASK ; 
 int /*<<< orphan*/  PCI_BUS_NUM (int) ; 
 int PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ alloc_ppr_log (struct amd_iommu*) ; 
 int /*<<< orphan*/  amd_iommu_ats_write_check_workaround (struct amd_iommu*) ; 
 int /*<<< orphan*/  amd_iommu_erratum_746_workaround (struct amd_iommu*) ; 
 int /*<<< orphan*/  amd_iommu_groups ; 
 int amd_iommu_iotlb_sup ; 
 int amd_iommu_max_glx_val ; 
 int amd_iommu_max_pasid ; 
 int amd_iommu_np_cache ; 
 int /*<<< orphan*/  amd_iommu_ops ; 
 int amd_iommu_v2_present ; 
 int /*<<< orphan*/  init_iommu_perf_ctr (struct amd_iommu*) ; 
 int /*<<< orphan*/  iommu_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_sysfs_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ iommu_feature (struct amd_iommu*,int /*<<< orphan*/ ) ; 
 int iommu_init_ga (struct amd_iommu*) ; 
 int /*<<< orphan*/  iommu_read_l1 (struct amd_iommu*,int,int) ; 
 int /*<<< orphan*/  iommu_read_l2 (struct amd_iommu*,int) ; 
 scalar_t__ is_rd890_iommu (TYPE_2__*) ; 
 int min (int,int) ; 
 int pci_enable_device (TYPE_2__*) ; 
 void* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_2__*,int,int*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int iommu_init_pci(struct amd_iommu *iommu)
{
	int cap_ptr = iommu->cap_ptr;
	u32 range, misc, low, high;
	int ret;

	iommu->dev = pci_get_domain_bus_and_slot(0, PCI_BUS_NUM(iommu->devid),
						 iommu->devid & 0xff);
	if (!iommu->dev)
		return -ENODEV;

	/* Prevent binding other PCI device drivers to IOMMU devices */
	iommu->dev->match_driver = false;

	pci_read_config_dword(iommu->dev, cap_ptr + MMIO_CAP_HDR_OFFSET,
			      &iommu->cap);
	pci_read_config_dword(iommu->dev, cap_ptr + MMIO_RANGE_OFFSET,
			      &range);
	pci_read_config_dword(iommu->dev, cap_ptr + MMIO_MISC_OFFSET,
			      &misc);

	if (!(iommu->cap & (1 << IOMMU_CAP_IOTLB)))
		amd_iommu_iotlb_sup = false;

	/* read extended feature bits */
	low  = readl(iommu->mmio_base + MMIO_EXT_FEATURES);
	high = readl(iommu->mmio_base + MMIO_EXT_FEATURES + 4);

	iommu->features = ((u64)high << 32) | low;

	if (iommu_feature(iommu, FEATURE_GT)) {
		int glxval;
		u32 max_pasid;
		u64 pasmax;

		pasmax = iommu->features & FEATURE_PASID_MASK;
		pasmax >>= FEATURE_PASID_SHIFT;
		max_pasid  = (1 << (pasmax + 1)) - 1;

		amd_iommu_max_pasid = min(amd_iommu_max_pasid, max_pasid);

		BUG_ON(amd_iommu_max_pasid & ~PASID_MASK);

		glxval   = iommu->features & FEATURE_GLXVAL_MASK;
		glxval >>= FEATURE_GLXVAL_SHIFT;

		if (amd_iommu_max_glx_val == -1)
			amd_iommu_max_glx_val = glxval;
		else
			amd_iommu_max_glx_val = min(amd_iommu_max_glx_val, glxval);
	}

	if (iommu_feature(iommu, FEATURE_GT) &&
	    iommu_feature(iommu, FEATURE_PPR)) {
		iommu->is_iommu_v2   = true;
		amd_iommu_v2_present = true;
	}

	if (iommu_feature(iommu, FEATURE_PPR) && alloc_ppr_log(iommu))
		return -ENOMEM;

	ret = iommu_init_ga(iommu);
	if (ret)
		return ret;

	if (iommu->cap & (1UL << IOMMU_CAP_NPCACHE))
		amd_iommu_np_cache = true;

	init_iommu_perf_ctr(iommu);

	if (is_rd890_iommu(iommu->dev)) {
		int i, j;

		iommu->root_pdev =
			pci_get_domain_bus_and_slot(0, iommu->dev->bus->number,
						    PCI_DEVFN(0, 0));

		/*
		 * Some rd890 systems may not be fully reconfigured by the
		 * BIOS, so it's necessary for us to store this information so
		 * it can be reprogrammed on resume
		 */
		pci_read_config_dword(iommu->dev, iommu->cap_ptr + 4,
				&iommu->stored_addr_lo);
		pci_read_config_dword(iommu->dev, iommu->cap_ptr + 8,
				&iommu->stored_addr_hi);

		/* Low bit locks writes to configuration space */
		iommu->stored_addr_lo &= ~1;

		for (i = 0; i < 6; i++)
			for (j = 0; j < 0x12; j++)
				iommu->stored_l1[i][j] = iommu_read_l1(iommu, i, j);

		for (i = 0; i < 0x83; i++)
			iommu->stored_l2[i] = iommu_read_l2(iommu, i);
	}

	amd_iommu_erratum_746_workaround(iommu);
	amd_iommu_ats_write_check_workaround(iommu);

	iommu_device_sysfs_add(&iommu->iommu, &iommu->dev->dev,
			       amd_iommu_groups, "ivhd%d", iommu->index);
	iommu_device_set_ops(&iommu->iommu, &amd_iommu_ops);
	iommu_device_register(&iommu->iommu);

	return pci_enable_device(iommu->dev);
}