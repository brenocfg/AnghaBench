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
struct iommu_cmd {int dummy; } ;
struct amd_iommu {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __iommu_queue_command_sync (struct amd_iommu*,struct iommu_cmd*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int iommu_queue_command_sync(struct amd_iommu *iommu,
				    struct iommu_cmd *cmd,
				    bool sync)
{
	unsigned long flags;
	int ret;

	raw_spin_lock_irqsave(&iommu->lock, flags);
	ret = __iommu_queue_command_sync(iommu, cmd, sync);
	raw_spin_unlock_irqrestore(&iommu->lock, flags);

	return ret;
}