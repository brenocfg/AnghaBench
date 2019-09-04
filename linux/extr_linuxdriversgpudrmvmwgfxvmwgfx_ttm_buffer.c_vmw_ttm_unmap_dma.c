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
struct TYPE_2__ {int /*<<< orphan*/ * sgt; } ;
struct vmw_ttm_tt {int mapped; int /*<<< orphan*/  sg_alloc_size; TYPE_1__ vsgt; struct vmw_private* dev_priv; } ;
struct vmw_private {int map_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_mem_global_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  vmw_dma_map_bind 129 
#define  vmw_dma_map_populate 128 
 int /*<<< orphan*/  vmw_mem_glob (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_ttm_unmap_from_dma (struct vmw_ttm_tt*) ; 

__attribute__((used)) static void vmw_ttm_unmap_dma(struct vmw_ttm_tt *vmw_tt)
{
	struct vmw_private *dev_priv = vmw_tt->dev_priv;

	if (!vmw_tt->vsgt.sgt)
		return;

	switch (dev_priv->map_mode) {
	case vmw_dma_map_bind:
	case vmw_dma_map_populate:
		vmw_ttm_unmap_from_dma(vmw_tt);
		sg_free_table(vmw_tt->vsgt.sgt);
		vmw_tt->vsgt.sgt = NULL;
		ttm_mem_global_free(vmw_mem_glob(dev_priv),
				    vmw_tt->sg_alloc_size);
		break;
	default:
		break;
	}
	vmw_tt->mapped = false;
}