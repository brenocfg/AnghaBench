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
typedef  int /*<<< orphan*/  u64 ;
struct iommu_cmd {int dummy; } ;
struct amd_iommu {int /*<<< orphan*/  lock; scalar_t__ cmd_sem; int /*<<< orphan*/  need_sync; } ;

/* Variables and functions */
 int __iommu_queue_command_sync (struct amd_iommu*,struct iommu_cmd*,int) ; 
 int /*<<< orphan*/  build_completion_wait (struct iommu_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_on_sem (scalar_t__*) ; 

__attribute__((used)) static int iommu_completion_wait(struct amd_iommu *iommu)
{
	struct iommu_cmd cmd;
	unsigned long flags;
	int ret;

	if (!iommu->need_sync)
		return 0;


	build_completion_wait(&cmd, (u64)&iommu->cmd_sem);

	raw_spin_lock_irqsave(&iommu->lock, flags);

	iommu->cmd_sem = 0;

	ret = __iommu_queue_command_sync(iommu, &cmd, false);
	if (ret)
		goto out_unlock;

	ret = wait_on_sem(&iommu->cmd_sem);

out_unlock:
	raw_spin_unlock_irqrestore(&iommu->lock, flags);

	return ret;
}