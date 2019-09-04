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
struct dmar_rmrr_unit {int /*<<< orphan*/  end_address; int /*<<< orphan*/  base_address; } ;
struct TYPE_2__ {scalar_t__ iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 scalar_t__ DUMMY_DEVICE_DOMAIN_INFO ; 
 int iommu_prepare_identity_map (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int iommu_prepare_rmrr_dev(struct dmar_rmrr_unit *rmrr,
					 struct device *dev)
{
	if (dev->archdata.iommu == DUMMY_DEVICE_DOMAIN_INFO)
		return 0;
	return iommu_prepare_identity_map(dev, rmrr->base_address,
					  rmrr->end_address);
}