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
typedef  int u16 ;
struct intel_iommu {int dummy; } ;
struct device_domain_info {int bus; int devfn; int ats_qdep; int pfsid; int /*<<< orphan*/  ats_enabled; } ;
struct TYPE_2__ {struct device_domain_info* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 scalar_t__ VTD_PAGE_SHIFT ; 
 int /*<<< orphan*/  qi_flush_dev_iotlb (struct intel_iommu*,int,int,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
devtlb_invalidation_with_pasid(struct intel_iommu *iommu,
			       struct device *dev, int pasid)
{
	struct device_domain_info *info;
	u16 sid, qdep, pfsid;

	info = dev->archdata.iommu;
	if (!info || !info->ats_enabled)
		return;

	sid = info->bus << 8 | info->devfn;
	qdep = info->ats_qdep;
	pfsid = info->pfsid;

	qi_flush_dev_iotlb(iommu, sid, pfsid, qdep, 0, 64 - VTD_PAGE_SHIFT);
}