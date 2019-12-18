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
struct tegra_bo {TYPE_1__* sgt; scalar_t__ pages; } ;
struct drm_gem_object {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct dma_buf {struct drm_gem_object* priv; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_sync_sg_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_bo* to_tegra_bo (struct drm_gem_object*) ; 

__attribute__((used)) static int tegra_gem_prime_end_cpu_access(struct dma_buf *buf,
					  enum dma_data_direction direction)
{
	struct drm_gem_object *gem = buf->priv;
	struct tegra_bo *bo = to_tegra_bo(gem);
	struct drm_device *drm = gem->dev;

	if (bo->pages)
		dma_sync_sg_for_device(drm->dev, bo->sgt->sgl, bo->sgt->nents,
				       DMA_TO_DEVICE);

	return 0;
}