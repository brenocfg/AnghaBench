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
struct tegra_drm {scalar_t__ domain; } ;
struct tegra_bo {int /*<<< orphan*/  sgt; } ;
struct drm_gem_object {TYPE_1__* dev; scalar_t__ import_attach; } ;
struct TYPE_2__ {struct tegra_drm* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_buf_unmap_attachment (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tegra_bo*) ; 
 int /*<<< orphan*/  tegra_bo_free (TYPE_1__*,struct tegra_bo*) ; 
 int /*<<< orphan*/  tegra_bo_iommu_unmap (struct tegra_drm*,struct tegra_bo*) ; 
 struct tegra_bo* to_tegra_bo (struct drm_gem_object*) ; 

void tegra_bo_free_object(struct drm_gem_object *gem)
{
	struct tegra_drm *tegra = gem->dev->dev_private;
	struct tegra_bo *bo = to_tegra_bo(gem);

	if (tegra->domain)
		tegra_bo_iommu_unmap(tegra, bo);

	if (gem->import_attach) {
		dma_buf_unmap_attachment(gem->import_attach, bo->sgt,
					 DMA_TO_DEVICE);
		drm_prime_gem_destroy(gem, NULL);
	} else {
		tegra_bo_free(gem->dev, bo);
	}

	drm_gem_object_release(gem);
	kfree(bo);
}