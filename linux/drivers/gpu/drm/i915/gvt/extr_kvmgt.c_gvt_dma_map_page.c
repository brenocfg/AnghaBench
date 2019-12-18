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
struct page {int dummy; } ;
struct intel_vgpu {TYPE_4__* gvt; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {TYPE_3__* dev_priv; } ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_7__ {TYPE_2__ drm; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_map_page (struct device*,struct page*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int gvt_pin_guest_page (struct intel_vgpu*,unsigned long,unsigned long,struct page**) ; 
 int /*<<< orphan*/  gvt_unpin_guest_page (struct intel_vgpu*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 

__attribute__((used)) static int gvt_dma_map_page(struct intel_vgpu *vgpu, unsigned long gfn,
		dma_addr_t *dma_addr, unsigned long size)
{
	struct device *dev = &vgpu->gvt->dev_priv->drm.pdev->dev;
	struct page *page = NULL;
	int ret;

	ret = gvt_pin_guest_page(vgpu, gfn, size, &page);
	if (ret)
		return ret;

	/* Setup DMA mapping. */
	*dma_addr = dma_map_page(dev, page, 0, size, PCI_DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, *dma_addr)) {
		gvt_vgpu_err("DMA mapping failed for pfn 0x%lx, ret %d\n",
			     page_to_pfn(page), ret);
		gvt_unpin_guest_page(vgpu, gfn, size);
		return -ENOMEM;
	}

	return 0;
}