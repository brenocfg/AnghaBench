#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_5__* scratch_pt; } ;
struct intel_vgpu {TYPE_6__ gtt; TYPE_4__* gvt; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_11__ {int page_mfn; int /*<<< orphan*/ * page; } ;
struct TYPE_10__ {TYPE_3__* dev_priv; } ;
struct TYPE_8__ {TYPE_1__* pdev; } ;
struct TYPE_9__ {TYPE_2__ drm; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 int GTT_TYPE_MAX ; 
 int GTT_TYPE_PPGTT_PTE_PT ; 
 int I915_GTT_PAGE_SHIFT ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int release_scratch_page_tree(struct intel_vgpu *vgpu)
{
	int i;
	struct device *dev = &vgpu->gvt->dev_priv->drm.pdev->dev;
	dma_addr_t daddr;

	for (i = GTT_TYPE_PPGTT_PTE_PT; i < GTT_TYPE_MAX; i++) {
		if (vgpu->gtt.scratch_pt[i].page != NULL) {
			daddr = (dma_addr_t)(vgpu->gtt.scratch_pt[i].page_mfn <<
					I915_GTT_PAGE_SHIFT);
			dma_unmap_page(dev, daddr, 4096, PCI_DMA_BIDIRECTIONAL);
			__free_page(vgpu->gtt.scratch_pt[i].page);
			vgpu->gtt.scratch_pt[i].page = NULL;
			vgpu->gtt.scratch_pt[i].page_mfn = 0;
		}
	}

	return 0;
}