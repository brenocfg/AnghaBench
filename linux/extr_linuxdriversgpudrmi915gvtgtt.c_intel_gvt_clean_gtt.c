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
struct TYPE_8__ {int scratch_mfn; int /*<<< orphan*/  scratch_page; } ;
struct intel_gvt {TYPE_4__ gtt; TYPE_3__* dev_priv; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_7__ {TYPE_2__ drm; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int I915_GTT_PAGE_SHIFT ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_spt_oos (struct intel_gvt*) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ enable_out_of_sync ; 

void intel_gvt_clean_gtt(struct intel_gvt *gvt)
{
	struct device *dev = &gvt->dev_priv->drm.pdev->dev;
	dma_addr_t daddr = (dma_addr_t)(gvt->gtt.scratch_mfn <<
					I915_GTT_PAGE_SHIFT);

	dma_unmap_page(dev, daddr, 4096, PCI_DMA_BIDIRECTIONAL);

	__free_page(gvt->gtt.scratch_page);

	if (enable_out_of_sync)
		clean_spt_oos(gvt);
}