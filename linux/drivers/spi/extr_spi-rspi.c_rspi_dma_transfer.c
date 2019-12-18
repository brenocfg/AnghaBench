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
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct rspi_data {unsigned int tx_irq; unsigned int rx_irq; TYPE_1__* ctlr; scalar_t__ dma_callbacked; int /*<<< orphan*/  wait; } ;
struct dma_async_tx_descriptor {struct rspi_data* callback_param; int /*<<< orphan*/ * callback; } ;
typedef  int dma_cookie_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  dma_tx; } ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  SPCR_SPRIE ; 
 int /*<<< orphan*/  SPCR_SPTIE ; 
 int /*<<< orphan*/  dev_driver_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (unsigned int) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_submit_error (int) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (unsigned int) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspi_disable_irq (struct rspi_data*,int /*<<< orphan*/ ) ; 
 void* rspi_dma_complete ; 
 int /*<<< orphan*/  rspi_enable_irq (struct rspi_data*,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rspi_dma_transfer(struct rspi_data *rspi, struct sg_table *tx,
			     struct sg_table *rx)
{
	struct dma_async_tx_descriptor *desc_tx = NULL, *desc_rx = NULL;
	u8 irq_mask = 0;
	unsigned int other_irq = 0;
	dma_cookie_t cookie;
	int ret;

	/* First prepare and submit the DMA request(s), as this may fail */
	if (rx) {
		desc_rx = dmaengine_prep_slave_sg(rspi->ctlr->dma_rx, rx->sgl,
					rx->nents, DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		if (!desc_rx) {
			ret = -EAGAIN;
			goto no_dma_rx;
		}

		desc_rx->callback = rspi_dma_complete;
		desc_rx->callback_param = rspi;
		cookie = dmaengine_submit(desc_rx);
		if (dma_submit_error(cookie)) {
			ret = cookie;
			goto no_dma_rx;
		}

		irq_mask |= SPCR_SPRIE;
	}

	if (tx) {
		desc_tx = dmaengine_prep_slave_sg(rspi->ctlr->dma_tx, tx->sgl,
					tx->nents, DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		if (!desc_tx) {
			ret = -EAGAIN;
			goto no_dma_tx;
		}

		if (rx) {
			/* No callback */
			desc_tx->callback = NULL;
		} else {
			desc_tx->callback = rspi_dma_complete;
			desc_tx->callback_param = rspi;
		}
		cookie = dmaengine_submit(desc_tx);
		if (dma_submit_error(cookie)) {
			ret = cookie;
			goto no_dma_tx;
		}

		irq_mask |= SPCR_SPTIE;
	}

	/*
	 * DMAC needs SPxIE, but if SPxIE is set, the IRQ routine will be
	 * called. So, this driver disables the IRQ while DMA transfer.
	 */
	if (tx)
		disable_irq(other_irq = rspi->tx_irq);
	if (rx && rspi->rx_irq != other_irq)
		disable_irq(rspi->rx_irq);

	rspi_enable_irq(rspi, irq_mask);
	rspi->dma_callbacked = 0;

	/* Now start DMA */
	if (rx)
		dma_async_issue_pending(rspi->ctlr->dma_rx);
	if (tx)
		dma_async_issue_pending(rspi->ctlr->dma_tx);

	ret = wait_event_interruptible_timeout(rspi->wait,
					       rspi->dma_callbacked, HZ);
	if (ret > 0 && rspi->dma_callbacked) {
		ret = 0;
	} else {
		if (!ret) {
			dev_err(&rspi->ctlr->dev, "DMA timeout\n");
			ret = -ETIMEDOUT;
		}
		if (tx)
			dmaengine_terminate_all(rspi->ctlr->dma_tx);
		if (rx)
			dmaengine_terminate_all(rspi->ctlr->dma_rx);
	}

	rspi_disable_irq(rspi, irq_mask);

	if (tx)
		enable_irq(rspi->tx_irq);
	if (rx && rspi->rx_irq != other_irq)
		enable_irq(rspi->rx_irq);

	return ret;

no_dma_tx:
	if (rx)
		dmaengine_terminate_all(rspi->ctlr->dma_rx);
no_dma_rx:
	if (ret == -EAGAIN) {
		pr_warn_once("%s %s: DMA not available, falling back to PIO\n",
			     dev_driver_string(&rspi->ctlr->dev),
			     dev_name(&rspi->ctlr->dev));
	}
	return ret;
}