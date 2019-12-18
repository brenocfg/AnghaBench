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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct mbox_controller {struct mbox_chan* chans; } ;
struct pdc_state {size_t rxin; scalar_t__ nrxpost; scalar_t__* txin_numd; size_t txin; scalar_t__ ntxpost; scalar_t__ pdc_resp_hdr_len; int /*<<< orphan*/  pdc_replies; int /*<<< orphan*/  rx_buf_pool; int /*<<< orphan*/  rx_oflow; int /*<<< orphan*/  last_rx_curr; int /*<<< orphan*/  rxout; int /*<<< orphan*/  txout; int /*<<< orphan*/  pdc_idx; struct pdc_rx_ctx* rx_ctx; int /*<<< orphan*/ * src_sg; struct mbox_controller mbc; TYPE_1__* pdev; } ;
struct pdc_rx_ctx {scalar_t__ rxin_numd; int /*<<< orphan*/  dst_sg; int /*<<< orphan*/  resp_hdr_daddr; int /*<<< orphan*/ * resp_hdr; int /*<<< orphan*/ * rxp_ctx; } ;
struct mbox_chan {int dummy; } ;
struct device {int dummy; } ;
struct brcm_message {int /*<<< orphan*/ * ctx; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCM_MESSAGE_SPU ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EIO ; 
 scalar_t__ NRXDACTIVE (size_t,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PDC_SPUM_RESP_HDR_LEN ; 
 int PDC_SUCCESS ; 
 scalar_t__ RX_STATUS_LEN ; 
 scalar_t__ RX_STATUS_OVERFLOW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_err_ratelimited (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info_ratelimited (struct device*,char*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_chan_received_data (struct mbox_chan*,struct brcm_message*) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
pdc_receive_one(struct pdc_state *pdcs)
{
	struct device *dev = &pdcs->pdev->dev;
	struct mbox_controller *mbc;
	struct mbox_chan *chan;
	struct brcm_message mssg;
	u32 len, rx_status;
	u32 num_frags;
	u8 *resp_hdr;    /* virtual addr of start of resp message DMA header */
	u32 frags_rdy;   /* number of fragments ready to read */
	u32 rx_idx;      /* ring index of start of receive frame */
	dma_addr_t resp_hdr_daddr;
	struct pdc_rx_ctx *rx_ctx;

	mbc = &pdcs->mbc;
	chan = &mbc->chans[0];
	mssg.type = BRCM_MESSAGE_SPU;

	/*
	 * return if a complete response message is not yet ready.
	 * rxin_numd[rxin] is the number of fragments in the next msg
	 * to read.
	 */
	frags_rdy = NRXDACTIVE(pdcs->rxin, pdcs->last_rx_curr, pdcs->nrxpost);
	if ((frags_rdy == 0) ||
	    (frags_rdy < pdcs->rx_ctx[pdcs->rxin].rxin_numd))
		/* No response ready */
		return -EAGAIN;

	num_frags = pdcs->txin_numd[pdcs->txin];
	WARN_ON(num_frags == 0);

	dma_unmap_sg(dev, pdcs->src_sg[pdcs->txin],
		     sg_nents(pdcs->src_sg[pdcs->txin]), DMA_TO_DEVICE);

	pdcs->txin = (pdcs->txin + num_frags) & pdcs->ntxpost;

	dev_dbg(dev, "PDC %u reclaimed %d tx descriptors",
		pdcs->pdc_idx, num_frags);

	rx_idx = pdcs->rxin;
	rx_ctx = &pdcs->rx_ctx[rx_idx];
	num_frags = rx_ctx->rxin_numd;
	/* Return opaque context with result */
	mssg.ctx = rx_ctx->rxp_ctx;
	rx_ctx->rxp_ctx = NULL;
	resp_hdr = rx_ctx->resp_hdr;
	resp_hdr_daddr = rx_ctx->resp_hdr_daddr;
	dma_unmap_sg(dev, rx_ctx->dst_sg, sg_nents(rx_ctx->dst_sg),
		     DMA_FROM_DEVICE);

	pdcs->rxin = (pdcs->rxin + num_frags) & pdcs->nrxpost;

	dev_dbg(dev, "PDC %u reclaimed %d rx descriptors",
		pdcs->pdc_idx, num_frags);

	dev_dbg(dev,
		"PDC %u txin %u, txout %u, rxin %u, rxout %u, last_rx_curr %u\n",
		pdcs->pdc_idx, pdcs->txin, pdcs->txout, pdcs->rxin,
		pdcs->rxout, pdcs->last_rx_curr);

	if (pdcs->pdc_resp_hdr_len == PDC_SPUM_RESP_HDR_LEN) {
		/*
		 * For SPU-M, get length of response msg and rx overflow status.
		 */
		rx_status = *((u32 *)resp_hdr);
		len = rx_status & RX_STATUS_LEN;
		dev_dbg(dev,
			"SPU response length %u bytes", len);
		if (unlikely(((rx_status & RX_STATUS_OVERFLOW) || (!len)))) {
			if (rx_status & RX_STATUS_OVERFLOW) {
				dev_err_ratelimited(dev,
						    "crypto receive overflow");
				pdcs->rx_oflow++;
			} else {
				dev_info_ratelimited(dev, "crypto rx len = 0");
			}
			return -EIO;
		}
	}

	dma_pool_free(pdcs->rx_buf_pool, resp_hdr, resp_hdr_daddr);

	mbox_chan_received_data(chan, &mssg);

	pdcs->pdc_replies++;
	return PDC_SUCCESS;
}