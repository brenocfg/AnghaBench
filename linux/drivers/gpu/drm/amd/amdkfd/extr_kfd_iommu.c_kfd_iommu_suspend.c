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
struct kfd_dev {int /*<<< orphan*/  pdev; TYPE_1__* device_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  needs_iommu_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_iommu_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_set_invalid_ppr_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amd_iommu_set_invalidate_ctx_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfd_unbind_processes_from_device (struct kfd_dev*) ; 

void kfd_iommu_suspend(struct kfd_dev *kfd)
{
	if (!kfd->device_info->needs_iommu_device)
		return;

	kfd_unbind_processes_from_device(kfd);

	amd_iommu_set_invalidate_ctx_cb(kfd->pdev, NULL);
	amd_iommu_set_invalid_ppr_cb(kfd->pdev, NULL);
	amd_iommu_free_device(kfd->pdev);
}