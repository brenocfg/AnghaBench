#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct vmw_sg_table {int mode; size_t num_pages; TYPE_4__* sgt; scalar_t__ num_regions; int /*<<< orphan*/  pages; int /*<<< orphan*/  addrs; } ;
struct TYPE_9__ {size_t nents; } ;
struct TYPE_6__ {size_t num_pages; int /*<<< orphan*/  pages; } ;
struct TYPE_7__ {int /*<<< orphan*/  dma_address; TYPE_1__ ttm; } ;
struct vmw_ttm_tt {int mapped; size_t sg_alloc_size; struct vmw_sg_table vsgt; TYPE_4__ sgt; TYPE_2__ dma_ttm; struct vmw_private* dev_priv; } ;
struct vmw_private {int map_mode; TYPE_3__* dev; } ;
struct vmw_piter {int dummy; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;
struct ttm_mem_global {int dummy; } ;
struct sg_table {int dummy; } ;
struct scatterlist {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int __sg_alloc_table_from_pages (TYPE_4__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_get_max_seg_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_4__*) ; 
 int ttm_mem_global_alloc (struct ttm_mem_global*,size_t,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_mem_global_free (struct ttm_mem_global*,size_t) ; 
 size_t ttm_round_pot (int) ; 
 int /*<<< orphan*/  unlikely (int) ; 
#define  vmw_dma_map_bind 129 
#define  vmw_dma_map_populate 128 
 struct ttm_mem_global* vmw_mem_glob (struct vmw_private*) ; 
 scalar_t__ vmw_piter_dma_addr (struct vmw_piter*) ; 
 scalar_t__ vmw_piter_next (struct vmw_piter*) ; 
 int /*<<< orphan*/  vmw_piter_start (struct vmw_piter*,struct vmw_sg_table*,int /*<<< orphan*/ ) ; 
 int vmw_ttm_map_for_dma (struct vmw_ttm_tt*) ; 

__attribute__((used)) static int vmw_ttm_map_dma(struct vmw_ttm_tt *vmw_tt)
{
	struct vmw_private *dev_priv = vmw_tt->dev_priv;
	struct ttm_mem_global *glob = vmw_mem_glob(dev_priv);
	struct vmw_sg_table *vsgt = &vmw_tt->vsgt;
	struct ttm_operation_ctx ctx = {
		.interruptible = true,
		.no_wait_gpu = false
	};
	struct vmw_piter iter;
	dma_addr_t old;
	int ret = 0;
	static size_t sgl_size;
	static size_t sgt_size;

	if (vmw_tt->mapped)
		return 0;

	vsgt->mode = dev_priv->map_mode;
	vsgt->pages = vmw_tt->dma_ttm.ttm.pages;
	vsgt->num_pages = vmw_tt->dma_ttm.ttm.num_pages;
	vsgt->addrs = vmw_tt->dma_ttm.dma_address;
	vsgt->sgt = &vmw_tt->sgt;

	switch (dev_priv->map_mode) {
	case vmw_dma_map_bind:
	case vmw_dma_map_populate:
		if (unlikely(!sgl_size)) {
			sgl_size = ttm_round_pot(sizeof(struct scatterlist));
			sgt_size = ttm_round_pot(sizeof(struct sg_table));
		}
		vmw_tt->sg_alloc_size = sgt_size + sgl_size * vsgt->num_pages;
		ret = ttm_mem_global_alloc(glob, vmw_tt->sg_alloc_size, &ctx);
		if (unlikely(ret != 0))
			return ret;

		ret = __sg_alloc_table_from_pages
			(&vmw_tt->sgt, vsgt->pages, vsgt->num_pages, 0,
			 (unsigned long) vsgt->num_pages << PAGE_SHIFT,
			 dma_get_max_seg_size(dev_priv->dev->dev),
			 GFP_KERNEL);
		if (unlikely(ret != 0))
			goto out_sg_alloc_fail;

		if (vsgt->num_pages > vmw_tt->sgt.nents) {
			uint64_t over_alloc =
				sgl_size * (vsgt->num_pages -
					    vmw_tt->sgt.nents);

			ttm_mem_global_free(glob, over_alloc);
			vmw_tt->sg_alloc_size -= over_alloc;
		}

		ret = vmw_ttm_map_for_dma(vmw_tt);
		if (unlikely(ret != 0))
			goto out_map_fail;

		break;
	default:
		break;
	}

	old = ~((dma_addr_t) 0);
	vmw_tt->vsgt.num_regions = 0;
	for (vmw_piter_start(&iter, vsgt, 0); vmw_piter_next(&iter);) {
		dma_addr_t cur = vmw_piter_dma_addr(&iter);

		if (cur != old + PAGE_SIZE)
			vmw_tt->vsgt.num_regions++;
		old = cur;
	}

	vmw_tt->mapped = true;
	return 0;

out_map_fail:
	sg_free_table(vmw_tt->vsgt.sgt);
	vmw_tt->vsgt.sgt = NULL;
out_sg_alloc_fail:
	ttm_mem_global_free(glob, vmw_tt->sg_alloc_size);
	return ret;
}