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
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct pdc_state {scalar_t__ nrxpost; size_t rxout; size_t rx_msg_start; int nrxd; int /*<<< orphan*/  pdc_resp_hdr_len; struct pdc_rx_ctx* rx_ctx; int /*<<< orphan*/  txout; int /*<<< orphan*/  tx_msg_start; int /*<<< orphan*/  rx_buf_pool; int /*<<< orphan*/  rxnobuf; int /*<<< orphan*/  rxin; } ;
struct pdc_rx_ctx {int rxin_numd; int /*<<< orphan*/  resp_hdr_daddr; void* resp_hdr; struct scatterlist* dst_sg; void* rxp_ctx; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ D64_CTRL1_EOT ; 
 scalar_t__ D64_CTRL1_SOF ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NRXDACTIVE (int /*<<< orphan*/ ,size_t,scalar_t__) ; 
 int PDC_SUCCESS ; 
 void* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdc_build_rxd (struct pdc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pdc_rx_list_init(struct pdc_state *pdcs, struct scatterlist *dst_sg,
			    void *ctx)
{
	u32 flags = 0;
	u32 rx_avail;
	u32 rx_pkt_cnt = 1;	/* Adding a single rx buffer */
	dma_addr_t daddr;
	void *vaddr;
	struct pdc_rx_ctx *rx_ctx;

	rx_avail = pdcs->nrxpost - NRXDACTIVE(pdcs->rxin, pdcs->rxout,
					      pdcs->nrxpost);
	if (unlikely(rx_pkt_cnt > rx_avail)) {
		pdcs->rxnobuf++;
		return -ENOSPC;
	}

	/* allocate a buffer for the dma rx status */
	vaddr = dma_pool_zalloc(pdcs->rx_buf_pool, GFP_ATOMIC, &daddr);
	if (unlikely(!vaddr))
		return -ENOMEM;

	/*
	 * Update msg_start indexes for both tx and rx to indicate the start
	 * of a new sequence of descriptor indexes that contain the fragments
	 * of the same message.
	 */
	pdcs->rx_msg_start = pdcs->rxout;
	pdcs->tx_msg_start = pdcs->txout;

	/* This is always the first descriptor in the receive sequence */
	flags = D64_CTRL1_SOF;
	pdcs->rx_ctx[pdcs->rx_msg_start].rxin_numd = 1;

	if (unlikely(pdcs->rxout == (pdcs->nrxd - 1)))
		flags |= D64_CTRL1_EOT;

	rx_ctx = &pdcs->rx_ctx[pdcs->rxout];
	rx_ctx->rxp_ctx = ctx;
	rx_ctx->dst_sg = dst_sg;
	rx_ctx->resp_hdr = vaddr;
	rx_ctx->resp_hdr_daddr = daddr;
	pdc_build_rxd(pdcs, daddr, pdcs->pdc_resp_hdr_len, flags);
	return PDC_SUCCESS;
}