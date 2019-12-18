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
struct TYPE_2__ {int /*<<< orphan*/  dev; struct iommu_domain* iommu_domain; } ;
struct venus_core {TYPE_1__ fw; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_detach_device (struct iommu_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_domain_free (struct iommu_domain*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (int /*<<< orphan*/ ) ; 

void venus_firmware_deinit(struct venus_core *core)
{
	struct iommu_domain *iommu;

	if (!core->fw.dev)
		return;

	iommu = core->fw.iommu_domain;

	iommu_detach_device(iommu, core->fw.dev);
	iommu_domain_free(iommu);

	platform_device_unregister(to_platform_device(core->fw.dev));
}