#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tegra_drm {int /*<<< orphan*/  mm_lock; TYPE_3__* drm; int /*<<< orphan*/  domain; int /*<<< orphan*/  mm; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct tegra_bo {TYPE_4__* mm; int /*<<< orphan*/  size; TYPE_2__* sgt; int /*<<< orphan*/  paddr; TYPE_1__ gem; } ;
struct TYPE_11__ {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int drm_mm_insert_node_generic (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_remove_node (TYPE_4__*) ; 
 int /*<<< orphan*/  iommu_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 TYPE_4__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_bo_iommu_map(struct tegra_drm *tegra, struct tegra_bo *bo)
{
	int prot = IOMMU_READ | IOMMU_WRITE;
	int err;

	if (bo->mm)
		return -EBUSY;

	bo->mm = kzalloc(sizeof(*bo->mm), GFP_KERNEL);
	if (!bo->mm)
		return -ENOMEM;

	mutex_lock(&tegra->mm_lock);

	err = drm_mm_insert_node_generic(&tegra->mm,
					 bo->mm, bo->gem.size, PAGE_SIZE, 0, 0);
	if (err < 0) {
		dev_err(tegra->drm->dev, "out of I/O virtual memory: %d\n",
			err);
		goto unlock;
	}

	bo->paddr = bo->mm->start;

	bo->size = iommu_map_sg(tegra->domain, bo->paddr, bo->sgt->sgl,
				bo->sgt->nents, prot);
	if (!bo->size) {
		dev_err(tegra->drm->dev, "failed to map buffer\n");
		err = -ENOMEM;
		goto remove;
	}

	mutex_unlock(&tegra->mm_lock);

	return 0;

remove:
	drm_mm_remove_node(bo->mm);
unlock:
	mutex_unlock(&tegra->mm_lock);
	kfree(bo->mm);
	return err;
}