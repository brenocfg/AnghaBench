#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  import_attach; } ;
struct armada_gem_object {int mapped; TYPE_2__* sgt; int /*<<< orphan*/  dev_addr; TYPE_1__ obj; } ;
struct TYPE_6__ {int nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 TYPE_2__* dma_buf_map_attachment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 scalar_t__ sg_dma_len (int /*<<< orphan*/ ) ; 

int armada_gem_map_import(struct armada_gem_object *dobj)
{
	int ret;

	dobj->sgt = dma_buf_map_attachment(dobj->obj.import_attach,
					   DMA_TO_DEVICE);
	if (IS_ERR(dobj->sgt)) {
		ret = PTR_ERR(dobj->sgt);
		dobj->sgt = NULL;
		DRM_ERROR("dma_buf_map_attachment() error: %d\n", ret);
		return ret;
	}
	if (dobj->sgt->nents > 1) {
		DRM_ERROR("dma_buf_map_attachment() returned an (unsupported) scattered list\n");
		return -EINVAL;
	}
	if (sg_dma_len(dobj->sgt->sgl) < dobj->obj.size) {
		DRM_ERROR("dma_buf_map_attachment() returned a small buffer\n");
		return -EINVAL;
	}
	dobj->dev_addr = sg_dma_address(dobj->sgt->sgl);
	dobj->mapped = true;
	return 0;
}