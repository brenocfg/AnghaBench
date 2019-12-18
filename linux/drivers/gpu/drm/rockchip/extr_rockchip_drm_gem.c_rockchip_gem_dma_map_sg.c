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
struct sg_table {int /*<<< orphan*/  sgl; int /*<<< orphan*/  nents; } ;
struct rockchip_gem_object {struct sg_table* sgt; int /*<<< orphan*/  dma_addr; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rockchip_sg_get_contiguous_size (struct sg_table*,int) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rockchip_gem_dma_map_sg(struct drm_device *drm,
			struct dma_buf_attachment *attach,
			struct sg_table *sg,
			struct rockchip_gem_object *rk_obj)
{
	int count = dma_map_sg(drm->dev, sg->sgl, sg->nents,
			       DMA_BIDIRECTIONAL);
	if (!count)
		return -EINVAL;

	if (rockchip_sg_get_contiguous_size(sg, count) < attach->dmabuf->size) {
		DRM_ERROR("failed to map sg_table to contiguous linear address.\n");
		dma_unmap_sg(drm->dev, sg->sgl, sg->nents,
			     DMA_BIDIRECTIONAL);
		return -EINVAL;
	}

	rk_obj->dma_addr = sg_dma_address(sg->sgl);
	rk_obj->sgt = sg;
	return 0;
}