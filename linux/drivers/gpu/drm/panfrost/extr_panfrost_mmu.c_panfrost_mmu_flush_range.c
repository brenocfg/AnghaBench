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
struct panfrost_mmu {scalar_t__ as; } ;
struct panfrost_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_COMMAND_FLUSH_PT ; 
 int /*<<< orphan*/  mmu_hw_do_operation (struct panfrost_device*,struct panfrost_mmu*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_runtime_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panfrost_mmu_flush_range(struct panfrost_device *pfdev,
				     struct panfrost_mmu *mmu,
				     u64 iova, size_t size)
{
	if (mmu->as < 0)
		return;

	pm_runtime_get_noresume(pfdev->dev);

	/* Flush the PTs only if we're already awake */
	if (pm_runtime_active(pfdev->dev))
		mmu_hw_do_operation(pfdev, mmu, iova, size, AS_COMMAND_FLUSH_PT);

	pm_runtime_put_sync_autosuspend(pfdev->dev);
}