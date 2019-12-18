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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct xdp_frame {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct page {int dummy; } ;
struct netsec_tx_pkt_ctrl {int dummy; } ;
struct netsec_priv {int /*<<< orphan*/  dev; struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {scalar_t__ head; scalar_t__ tail; int /*<<< orphan*/  page_pool; } ;
struct netsec_desc {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; scalar_t__ dma_addr; int /*<<< orphan*/  buf_type; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int DESC_NUM ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 size_t NETSEC_RING_RX ; 
 size_t NETSEC_RING_TX ; 
 scalar_t__ NETSEC_RXBUF_HEADROOM ; 
 int /*<<< orphan*/  NETSEC_XDP_CONSUMED ; 
 int /*<<< orphan*/  NETSEC_XDP_TX ; 
 int /*<<< orphan*/  TYPE_NETSEC_XDP_NDO ; 
 int /*<<< orphan*/  TYPE_NETSEC_XDP_TX ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netsec_set_tx_de (struct netsec_priv*,struct netsec_desc_ring*,struct netsec_tx_pkt_ctrl*,struct netsec_desc*,struct xdp_frame*) ; 
 scalar_t__ page_pool_get_dma_addr (struct page*) ; 
 int page_pool_get_dma_dir (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 netsec_xdp_queue_one(struct netsec_priv *priv,
				struct xdp_frame *xdpf, bool is_ndo)

{
	struct netsec_desc_ring *tx_ring = &priv->desc_ring[NETSEC_RING_TX];
	struct page *page = virt_to_page(xdpf->data);
	struct netsec_tx_pkt_ctrl tx_ctrl = {};
	struct netsec_desc tx_desc;
	dma_addr_t dma_handle;
	u16 filled;

	if (tx_ring->head >= tx_ring->tail)
		filled = tx_ring->head - tx_ring->tail;
	else
		filled = tx_ring->head + DESC_NUM - tx_ring->tail;

	if (DESC_NUM - filled <= 1)
		return NETSEC_XDP_CONSUMED;

	if (is_ndo) {
		/* this is for ndo_xdp_xmit, the buffer needs mapping before
		 * sending
		 */
		dma_handle = dma_map_single(priv->dev, xdpf->data, xdpf->len,
					    DMA_TO_DEVICE);
		if (dma_mapping_error(priv->dev, dma_handle))
			return NETSEC_XDP_CONSUMED;
		tx_desc.buf_type = TYPE_NETSEC_XDP_NDO;
	} else {
		/* This is the device Rx buffer from page_pool. No need to remap
		 * just sync and send it
		 */
		struct netsec_desc_ring *rx_ring =
			&priv->desc_ring[NETSEC_RING_RX];
		enum dma_data_direction dma_dir =
			page_pool_get_dma_dir(rx_ring->page_pool);

		dma_handle = page_pool_get_dma_addr(page) +
			NETSEC_RXBUF_HEADROOM;
		dma_sync_single_for_device(priv->dev, dma_handle, xdpf->len,
					   dma_dir);
		tx_desc.buf_type = TYPE_NETSEC_XDP_TX;
	}

	tx_desc.dma_addr = dma_handle;
	tx_desc.addr = xdpf->data;
	tx_desc.len = xdpf->len;

	netsec_set_tx_de(priv, tx_ring, &tx_ctrl, &tx_desc, xdpf);

	return NETSEC_XDP_TX;
}