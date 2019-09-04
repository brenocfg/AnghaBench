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
 struct page* dev_alloc_page () ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* napi_alloc_frag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_dma_map_rx (struct nfp_net_dp*,void*) ; 
 int /*<<< orphan*/  nfp_net_free_frag (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_dp_warn (struct nfp_net_dp*,char*) ; 
 void* page_address (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *nfp_net_napi_alloc_one(struct nfp_net_dp *dp, dma_addr_t *dma_addr)
{
	void *frag;

	if (!dp->xdp_prog) {
		frag = napi_alloc_frag(dp->fl_bufsz);
		if (unlikely(!frag))
			return NULL;
	} else {
		struct page *page;

		page = dev_alloc_page();
		if (unlikely(!page))
			return NULL;
		frag = page_address(page);
	}

	*dma_addr = nfp_net_dma_map_rx(dp, frag);
	if (dma_mapping_error(dp->dev, *dma_addr)) {
		nfp_net_free_frag(frag, dp->xdp_prog);
		nn_dp_warn(dp, "Failed to map DMA RX buffer\n");
		return NULL;
	}

	return frag;
}