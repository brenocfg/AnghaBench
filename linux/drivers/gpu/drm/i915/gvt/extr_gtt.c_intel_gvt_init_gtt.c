#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned long scratch_mfn; int /*<<< orphan*/  ppgtt_mm_lock; int /*<<< orphan*/  ppgtt_mm_lru_list_head; int /*<<< orphan*/  scratch_page; int /*<<< orphan*/ * gma_ops; int /*<<< orphan*/ * pte_ops; } ;
struct intel_gvt {TYPE_4__ gtt; TYPE_3__* dev_priv; } ;
struct device {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_7__ {TYPE_2__ drm; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I915_GTT_PAGE_SHIFT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int dma_map_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ enable_out_of_sync ; 
 int /*<<< orphan*/  gen8_gtt_gma_ops ; 
 int /*<<< orphan*/  gen8_gtt_pte_ops ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*) ; 
 int /*<<< orphan*/  gvt_err (char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int setup_spt_oos (struct intel_gvt*) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

int intel_gvt_init_gtt(struct intel_gvt *gvt)
{
	int ret;
	void *page;
	struct device *dev = &gvt->dev_priv->drm.pdev->dev;
	dma_addr_t daddr;

	gvt_dbg_core("init gtt\n");

	gvt->gtt.pte_ops = &gen8_gtt_pte_ops;
	gvt->gtt.gma_ops = &gen8_gtt_gma_ops;

	page = (void *)get_zeroed_page(GFP_KERNEL);
	if (!page) {
		gvt_err("fail to allocate scratch ggtt page\n");
		return -ENOMEM;
	}

	daddr = dma_map_page(dev, virt_to_page(page), 0,
			4096, PCI_DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, daddr)) {
		gvt_err("fail to dmamap scratch ggtt page\n");
		__free_page(virt_to_page(page));
		return -ENOMEM;
	}

	gvt->gtt.scratch_page = virt_to_page(page);
	gvt->gtt.scratch_mfn = (unsigned long)(daddr >> I915_GTT_PAGE_SHIFT);

	if (enable_out_of_sync) {
		ret = setup_spt_oos(gvt);
		if (ret) {
			gvt_err("fail to initialize SPT oos\n");
			dma_unmap_page(dev, daddr, 4096, PCI_DMA_BIDIRECTIONAL);
			__free_page(gvt->gtt.scratch_page);
			return ret;
		}
	}
	INIT_LIST_HEAD(&gvt->gtt.ppgtt_mm_lru_list_head);
	mutex_init(&gvt->gtt.ppgtt_mm_lock);
	return 0;
}