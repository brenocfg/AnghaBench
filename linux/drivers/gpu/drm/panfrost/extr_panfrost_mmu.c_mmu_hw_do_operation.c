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
typedef  int /*<<< orphan*/  u32 ;
struct panfrost_mmu {int /*<<< orphan*/  as; } ;
struct panfrost_device {int /*<<< orphan*/  as_lock; } ;

/* Variables and functions */
 int mmu_hw_do_operation_locked (struct panfrost_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmu_hw_do_operation(struct panfrost_device *pfdev,
			       struct panfrost_mmu *mmu,
			       u64 iova, size_t size, u32 op)
{
	int ret;

	spin_lock(&pfdev->as_lock);
	ret = mmu_hw_do_operation_locked(pfdev, mmu->as, iova, size, op);
	spin_unlock(&pfdev->as_lock);
	return ret;
}