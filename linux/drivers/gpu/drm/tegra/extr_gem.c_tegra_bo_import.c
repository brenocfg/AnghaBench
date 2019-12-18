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
struct TYPE_2__ {struct tegra_bo* import_attach; } ;
struct tegra_bo {int nents; TYPE_1__ gem; struct tegra_bo* sgt; int /*<<< orphan*/  sgl; int /*<<< orphan*/  paddr; } ;
struct drm_device {int /*<<< orphan*/  dev; struct tegra_drm* dev_private; } ;
struct dma_buf_attachment {int nents; TYPE_1__ gem; struct dma_buf_attachment* sgt; int /*<<< orphan*/  sgl; int /*<<< orphan*/  paddr; } ;
struct dma_buf {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 struct tegra_bo* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct tegra_bo*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct tegra_bo*) ; 
 int PTR_ERR (struct tegra_bo*) ; 
 struct tegra_bo* dma_buf_attach (struct dma_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_detach (struct dma_buf*,struct tegra_bo*) ; 
 struct tegra_bo* dma_buf_map_attachment (struct tegra_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 int /*<<< orphan*/  dma_buf_unmap_attachment (struct tegra_bo*,struct tegra_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_release (TYPE_1__*) ; 
 int /*<<< orphan*/  get_dma_buf (struct dma_buf*) ; 
 int /*<<< orphan*/  kfree (struct tegra_bo*) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 struct tegra_bo* tegra_bo_alloc_object (struct drm_device*,int /*<<< orphan*/ ) ; 
 int tegra_bo_iommu_map (struct tegra_drm*,struct tegra_bo*) ; 

__attribute__((used)) static struct tegra_bo *tegra_bo_import(struct drm_device *drm,
					struct dma_buf *buf)
{
	struct tegra_drm *tegra = drm->dev_private;
	struct dma_buf_attachment *attach;
	struct tegra_bo *bo;
	int err;

	bo = tegra_bo_alloc_object(drm, buf->size);
	if (IS_ERR(bo))
		return bo;

	attach = dma_buf_attach(buf, drm->dev);
	if (IS_ERR(attach)) {
		err = PTR_ERR(attach);
		goto free;
	}

	get_dma_buf(buf);

	bo->sgt = dma_buf_map_attachment(attach, DMA_TO_DEVICE);
	if (IS_ERR(bo->sgt)) {
		err = PTR_ERR(bo->sgt);
		goto detach;
	}

	if (tegra->domain) {
		err = tegra_bo_iommu_map(tegra, bo);
		if (err < 0)
			goto detach;
	} else {
		if (bo->sgt->nents > 1) {
			err = -EINVAL;
			goto detach;
		}

		bo->paddr = sg_dma_address(bo->sgt->sgl);
	}

	bo->gem.import_attach = attach;

	return bo;

detach:
	if (!IS_ERR_OR_NULL(bo->sgt))
		dma_buf_unmap_attachment(attach, bo->sgt, DMA_TO_DEVICE);

	dma_buf_detach(buf, attach);
	dma_buf_put(buf);
free:
	drm_gem_object_release(&bo->gem);
	kfree(bo);
	return ERR_PTR(err);
}