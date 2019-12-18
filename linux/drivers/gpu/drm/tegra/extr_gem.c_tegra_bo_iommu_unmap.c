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
struct tegra_drm {int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  domain; } ;
struct tegra_bo {int /*<<< orphan*/  mm; int /*<<< orphan*/  size; int /*<<< orphan*/  paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_bo_iommu_unmap(struct tegra_drm *tegra, struct tegra_bo *bo)
{
	if (!bo->mm)
		return 0;

	mutex_lock(&tegra->mm_lock);
	iommu_unmap(tegra->domain, bo->paddr, bo->size);
	drm_mm_remove_node(bo->mm);
	mutex_unlock(&tegra->mm_lock);

	kfree(bo->mm);

	return 0;
}