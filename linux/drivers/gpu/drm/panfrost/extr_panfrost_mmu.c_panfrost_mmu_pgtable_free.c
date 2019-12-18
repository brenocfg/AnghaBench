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
struct panfrost_mmu {scalar_t__ as; int /*<<< orphan*/  pgtbl_ops; int /*<<< orphan*/  list; } ;
struct panfrost_file_priv {struct panfrost_mmu mmu; struct panfrost_device* pfdev; } ;
struct panfrost_device {int /*<<< orphan*/  as_lock; int /*<<< orphan*/  as_in_use_mask; int /*<<< orphan*/  as_alloc_mask; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_io_pgtable_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panfrost_mmu_disable (struct panfrost_device*,scalar_t__) ; 
 scalar_t__ pm_runtime_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void panfrost_mmu_pgtable_free(struct panfrost_file_priv *priv)
{
	struct panfrost_device *pfdev = priv->pfdev;
	struct panfrost_mmu *mmu = &priv->mmu;

	spin_lock(&pfdev->as_lock);
	if (mmu->as >= 0) {
		pm_runtime_get_noresume(pfdev->dev);
		if (pm_runtime_active(pfdev->dev))
			panfrost_mmu_disable(pfdev, mmu->as);
		pm_runtime_put_autosuspend(pfdev->dev);

		clear_bit(mmu->as, &pfdev->as_alloc_mask);
		clear_bit(mmu->as, &pfdev->as_in_use_mask);
		list_del(&mmu->list);
	}
	spin_unlock(&pfdev->as_lock);

	free_io_pgtable_ops(mmu->pgtbl_ops);
}