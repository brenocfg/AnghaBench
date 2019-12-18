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
typedef  int /*<<< orphan*/  u16 ;
struct page_pool_params {int pool_size; int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  dev; int /*<<< orphan*/  nid; int /*<<< orphan*/  flags; scalar_t__ order; int /*<<< orphan*/  member_0; } ;
struct netsec_priv {int /*<<< orphan*/  ndev; int /*<<< orphan*/  dev; int /*<<< orphan*/  xdp_prog; struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {struct netsec_desc* desc; int /*<<< orphan*/ * page_pool; int /*<<< orphan*/  xdp_rxq; } ;
struct netsec_desc {int /*<<< orphan*/  len; void* addr; int /*<<< orphan*/  dma_addr; } ;
struct bpf_prog {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DESC_NUM ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEM_TYPE_PAGE_POOL ; 
 size_t NETSEC_RING_RX ; 
 int /*<<< orphan*/  PP_FLAG_DMA_MAP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_node (int /*<<< orphan*/ ) ; 
 void* netsec_alloc_rx_data (struct netsec_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netsec_rx_fill (struct netsec_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netsec_uninit_pkt_dring (struct netsec_priv*,size_t) ; 
 int /*<<< orphan*/ * page_pool_create (struct page_pool_params*) ; 
 int xdp_rxq_info_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xdp_rxq_info_reg_mem_model (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netsec_setup_rx_dring(struct netsec_priv *priv)
{
	struct netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_RX];
	struct bpf_prog *xdp_prog = READ_ONCE(priv->xdp_prog);
	struct page_pool_params pp_params = { 0 };
	int i, err;

	pp_params.order = 0;
	/* internal DMA mapping in page_pool */
	pp_params.flags = PP_FLAG_DMA_MAP;
	pp_params.pool_size = DESC_NUM;
	pp_params.nid = cpu_to_node(0);
	pp_params.dev = priv->dev;
	pp_params.dma_dir = xdp_prog ? DMA_BIDIRECTIONAL : DMA_FROM_DEVICE;

	dring->page_pool = page_pool_create(&pp_params);
	if (IS_ERR(dring->page_pool)) {
		err = PTR_ERR(dring->page_pool);
		dring->page_pool = NULL;
		goto err_out;
	}

	err = xdp_rxq_info_reg(&dring->xdp_rxq, priv->ndev, 0);
	if (err)
		goto err_out;

	err = xdp_rxq_info_reg_mem_model(&dring->xdp_rxq, MEM_TYPE_PAGE_POOL,
					 dring->page_pool);
	if (err)
		goto err_out;

	for (i = 0; i < DESC_NUM; i++) {
		struct netsec_desc *desc = &dring->desc[i];
		dma_addr_t dma_handle;
		void *buf;
		u16 len;

		buf = netsec_alloc_rx_data(priv, &dma_handle, &len);

		if (!buf) {
			err = -ENOMEM;
			goto err_out;
		}
		desc->dma_addr = dma_handle;
		desc->addr = buf;
		desc->len = len;
	}

	netsec_rx_fill(priv, 0, DESC_NUM);

	return 0;

err_out:
	netsec_uninit_pkt_dring(priv, NETSEC_RING_RX);
	return err;
}