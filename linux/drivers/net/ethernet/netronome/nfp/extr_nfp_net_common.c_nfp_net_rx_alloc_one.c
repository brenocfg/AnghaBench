#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct page {int dummy; } ;
struct nfp_net_dp {int /*<<< orphan*/  xdp_prog; int /*<<< orphan*/  dev; int /*<<< orphan*/  fl_bufsz; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* netdev_alloc_frag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_dma_map_rx (struct nfp_net_dp*,void*) ; 
 int /*<<< orphan*/  nfp_net_free_frag (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_dp_warn (struct nfp_net_dp*,char*) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 

__attribute__((used)) static void *nfp_net_rx_alloc_one(struct nfp_net_dp *dp, dma_addr_t *dma_addr)
{
	void *frag;

	if (!dp->xdp_prog) {
		frag = netdev_alloc_frag(dp->fl_bufsz);
	} else {
		struct page *page;

		page = alloc_page(GFP_KERNEL);
		frag = page ? page_address(page) : NULL;
	}
	if (!frag) {
		nn_dp_warn(dp, "Failed to alloc receive page frag\n");
		return NULL;
	}

	*dma_addr = nfp_net_dma_map_rx(dp, frag);
	if (dma_mapping_error(dp->dev, *dma_addr)) {
		nfp_net_free_frag(frag, dp->xdp_prog);
		nn_dp_warn(dp, "Failed to map DMA RX buffer\n");
		return NULL;
	}

	return frag;
}