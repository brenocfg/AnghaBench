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
 int ENXIO ; 
 int /*<<< orphan*/  amd_iommu_free_device (int /*<<< orphan*/ ) ; 
 int amd_iommu_init_device (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  amd_iommu_set_invalid_ppr_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amd_iommu_set_invalidate_ctx_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iommu_invalid_ppr_cb ; 
 int /*<<< orphan*/ * iommu_pasid_shutdown_callback ; 
 int kfd_bind_processes_to_device (struct kfd_dev*) ; 
 unsigned int kfd_get_pasid_limit () ; 

int kfd_iommu_resume(struct kfd_dev *kfd)
{
	unsigned int pasid_limit;
	int err;

	if (!kfd->device_info->needs_iommu_device)
		return 0;

	pasid_limit = kfd_get_pasid_limit();

	err = amd_iommu_init_device(kfd->pdev, pasid_limit);
	if (err)
		return -ENXIO;

	amd_iommu_set_invalidate_ctx_cb(kfd->pdev,
					iommu_pasid_shutdown_callback);
	amd_iommu_set_invalid_ppr_cb(kfd->pdev,
				     iommu_invalid_ppr_cb);

	err = kfd_bind_processes_to_device(kfd);
	if (err) {
		amd_iommu_set_invalidate_ctx_cb(kfd->pdev, NULL);
		amd_iommu_set_invalid_ppr_cb(kfd->pdev, NULL);
		amd_iommu_free_device(kfd->pdev);
		return err;
	}

	return 0;
}