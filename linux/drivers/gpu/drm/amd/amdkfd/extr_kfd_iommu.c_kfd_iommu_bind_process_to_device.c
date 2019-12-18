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
struct kfd_process_device {scalar_t__ bound; struct kfd_process* process; struct kfd_dev* dev; } ;
struct kfd_process {int /*<<< orphan*/  lead_thread; int /*<<< orphan*/  pasid; } ;
struct kfd_dev {int /*<<< orphan*/  pdev; TYPE_1__* device_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  needs_iommu_device; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PDD_BOUND ; 
 scalar_t__ PDD_BOUND_SUSPENDED ; 
 int amd_iommu_bind_pasid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ unlikely (int) ; 

int kfd_iommu_bind_process_to_device(struct kfd_process_device *pdd)
{
	struct kfd_dev *dev = pdd->dev;
	struct kfd_process *p = pdd->process;
	int err;

	if (!dev->device_info->needs_iommu_device || pdd->bound == PDD_BOUND)
		return 0;

	if (unlikely(pdd->bound == PDD_BOUND_SUSPENDED)) {
		pr_err("Binding PDD_BOUND_SUSPENDED pdd is unexpected!\n");
		return -EINVAL;
	}

	err = amd_iommu_bind_pasid(dev->pdev, p->pasid, p->lead_thread);
	if (!err)
		pdd->bound = PDD_BOUND;

	return err;
}