#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kfd_dev {TYPE_1__* pdev; TYPE_3__* dqm; } ;
struct TYPE_5__ {int (* start ) (TYPE_3__*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfd_device ; 
 int kfd_iommu_resume (struct kfd_dev*) ; 
 int /*<<< orphan*/  kfd_iommu_suspend (struct kfd_dev*) ; 
 int stub1 (TYPE_3__*) ; 

__attribute__((used)) static int kfd_resume(struct kfd_dev *kfd)
{
	int err = 0;

	err = kfd_iommu_resume(kfd);
	if (err) {
		dev_err(kfd_device,
			"Failed to resume IOMMU for device %x:%x\n",
			kfd->pdev->vendor, kfd->pdev->device);
		return err;
	}

	err = kfd->dqm->ops.start(kfd->dqm);
	if (err) {
		dev_err(kfd_device,
			"Error starting queue manager for device %x:%x\n",
			kfd->pdev->vendor, kfd->pdev->device);
		goto dqm_start_error;
	}

	return err;

dqm_start_error:
	kfd_iommu_suspend(kfd);
	return err;
}