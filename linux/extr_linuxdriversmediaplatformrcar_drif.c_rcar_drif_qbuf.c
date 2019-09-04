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
struct rcar_drif_sdr {int hwbuf_size; } ;
struct rcar_drif {int /*<<< orphan*/  dmach; int /*<<< orphan*/  num; int /*<<< orphan*/  dma_handle; struct rcar_drif_sdr* sdr; } ;
struct dma_async_tx_descriptor {struct rcar_drif* callback_param; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int DMA_PREP_INTERRUPT ; 
 int EIO ; 
 int RCAR_DRIF_NUM_HWBUFS ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_submit_error (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_dma_cyclic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  rcar_drif_dma_complete ; 
 int /*<<< orphan*/  rdrif_err (struct rcar_drif_sdr*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_drif_qbuf(struct rcar_drif *ch)
{
	struct rcar_drif_sdr *sdr = ch->sdr;
	dma_addr_t addr = ch->dma_handle;
	struct dma_async_tx_descriptor *rxd;
	dma_cookie_t cookie;
	int ret = -EIO;

	/* Setup cyclic DMA with given buffers */
	rxd = dmaengine_prep_dma_cyclic(ch->dmach, addr,
					sdr->hwbuf_size * RCAR_DRIF_NUM_HWBUFS,
					sdr->hwbuf_size, DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!rxd) {
		rdrif_err(sdr, "ch%u: prep dma cyclic failed\n", ch->num);
		return ret;
	}

	/* Submit descriptor */
	rxd->callback = rcar_drif_dma_complete;
	rxd->callback_param = ch;
	cookie = dmaengine_submit(rxd);
	if (dma_submit_error(cookie)) {
		rdrif_err(sdr, "ch%u: dma submit failed\n", ch->num);
		return ret;
	}

	dma_async_issue_pending(ch->dmach);
	return 0;
}