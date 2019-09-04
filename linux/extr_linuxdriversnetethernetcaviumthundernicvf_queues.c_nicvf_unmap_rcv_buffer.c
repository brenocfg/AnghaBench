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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct nicvf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_MASK ; 
 int RCV_FRAG_LEN ; 
 scalar_t__ XDP_PACKET_HEADROOM ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int page_ref_count (struct page*) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nicvf_unmap_rcv_buffer(struct nicvf *nic, u64 dma_addr,
				   u64 buf_addr, bool xdp)
{
	struct page *page = NULL;
	int len = RCV_FRAG_LEN;

	if (xdp) {
		page = virt_to_page(phys_to_virt(buf_addr));
		/* Check if it's a recycled page, if not
		 * unmap the DMA mapping.
		 *
		 * Recycled page holds an extra reference.
		 */
		if (page_ref_count(page) != 1)
			return;

		len += XDP_PACKET_HEADROOM;
		/* Receive buffers in XDP mode are mapped from page start */
		dma_addr &= PAGE_MASK;
	}
	dma_unmap_page_attrs(&nic->pdev->dev, dma_addr, len,
			     DMA_FROM_DEVICE, DMA_ATTR_SKIP_CPU_SYNC);
}