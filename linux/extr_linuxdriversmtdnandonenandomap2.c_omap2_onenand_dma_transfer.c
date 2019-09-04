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
struct omap2_onenand {int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  dma_done; TYPE_1__* pdev; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  (* tx_submit ) (struct dma_async_tx_descriptor*) ;int /*<<< orphan*/ * callback_param; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_submit_error (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_dma_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  omap2_onenand_dma_complete_func ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  wait_for_completion_io_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int omap2_onenand_dma_transfer(struct omap2_onenand *c,
					     dma_addr_t src, dma_addr_t dst,
					     size_t count)
{
	struct dma_async_tx_descriptor *tx;
	dma_cookie_t cookie;

	tx = dmaengine_prep_dma_memcpy(c->dma_chan, dst, src, count, 0);
	if (!tx) {
		dev_err(&c->pdev->dev, "Failed to prepare DMA memcpy\n");
		return -EIO;
	}

	reinit_completion(&c->dma_done);

	tx->callback = omap2_onenand_dma_complete_func;
	tx->callback_param = &c->dma_done;

	cookie = tx->tx_submit(tx);
	if (dma_submit_error(cookie)) {
		dev_err(&c->pdev->dev, "Failed to do DMA tx_submit\n");
		return -EIO;
	}

	dma_async_issue_pending(c->dma_chan);

	if (!wait_for_completion_io_timeout(&c->dma_done,
					    msecs_to_jiffies(20))) {
		dmaengine_terminate_sync(c->dma_chan);
		return -ETIMEDOUT;
	}

	return 0;
}