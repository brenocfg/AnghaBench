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
struct usbhs_priv {int dummy; } ;
struct usbhs_pkt {int /*<<< orphan*/  trans; int /*<<< orphan*/  zero; int /*<<< orphan*/  length; int /*<<< orphan*/  cookie; scalar_t__ actual; scalar_t__ dma; struct usbhs_pipe* pipe; } ;
struct usbhs_pipe {int dummy; } ;
struct usbhs_fifo {int /*<<< orphan*/  name; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {struct usbhs_pipe* callback_param; int /*<<< orphan*/  callback; } ;
struct device {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_single (struct dma_chan*,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  usbhs_pipe_enable (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_is_dir_in (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_number (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_running (struct usbhs_pipe*,int) ; 
 int /*<<< orphan*/  usbhs_pipe_set_trans_count_if_bulk (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 struct usbhs_fifo* usbhs_pipe_to_fifo (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 struct dma_chan* usbhsf_dma_chan_get (struct usbhs_fifo*,struct usbhs_pkt*) ; 
 int /*<<< orphan*/  usbhsf_dma_complete ; 
 int /*<<< orphan*/  usbhsf_dma_start (struct usbhs_pipe*,struct usbhs_fifo*) ; 

__attribute__((used)) static void usbhsf_dma_xfer_preparing(struct usbhs_pkt *pkt)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	struct usbhs_fifo *fifo;
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct dma_async_tx_descriptor *desc;
	struct dma_chan *chan;
	struct device *dev = usbhs_priv_to_dev(priv);
	enum dma_transfer_direction dir;

	fifo = usbhs_pipe_to_fifo(pipe);
	if (!fifo)
		return;

	chan = usbhsf_dma_chan_get(fifo, pkt);
	dir = usbhs_pipe_is_dir_in(pipe) ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV;

	desc = dmaengine_prep_slave_single(chan, pkt->dma + pkt->actual,
					pkt->trans, dir,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc)
		return;

	desc->callback		= usbhsf_dma_complete;
	desc->callback_param	= pipe;

	pkt->cookie = dmaengine_submit(desc);
	if (pkt->cookie < 0) {
		dev_err(dev, "Failed to submit dma descriptor\n");
		return;
	}

	dev_dbg(dev, "  %s %d (%d/ %d)\n",
		fifo->name, usbhs_pipe_number(pipe), pkt->length, pkt->zero);

	usbhs_pipe_running(pipe, 1);
	usbhs_pipe_set_trans_count_if_bulk(pipe, pkt->trans);
	dma_async_issue_pending(chan);
	usbhsf_dma_start(pipe, fifo);
	usbhs_pipe_enable(pipe);
}