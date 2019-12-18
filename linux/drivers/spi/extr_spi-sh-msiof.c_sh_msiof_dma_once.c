#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sh_msiof_spi_priv {int slave_aborted; TYPE_3__* ctlr; int /*<<< orphan*/  rx_dma_addr; TYPE_1__* pdev; int /*<<< orphan*/  done; int /*<<< orphan*/  done_txdma; int /*<<< orphan*/  tx_dma_addr; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/ * callback_param; void* callback; } ;
typedef  int dma_cookie_t ;
struct TYPE_10__ {TYPE_2__* device; } ;
struct TYPE_9__ {TYPE_4__* dma_rx; TYPE_4__* dma_tx; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  FCTR ; 
 int FCTR_RFWM_1 ; 
 int FCTR_TFWM_1 ; 
 int /*<<< orphan*/  IER ; 
 int IER_RDMAE ; 
 int IER_RDREQE ; 
 int IER_TDMAE ; 
 int IER_TDREQE ; 
 int IER_TEOFE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (TYPE_4__*) ; 
 scalar_t__ dma_submit_error (int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_single (TYPE_4__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 int dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (TYPE_4__*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 void* sh_msiof_dma_complete ; 
 int /*<<< orphan*/  sh_msiof_reset_str (struct sh_msiof_spi_priv*) ; 
 int /*<<< orphan*/  sh_msiof_spi_set_mode_regs (struct sh_msiof_spi_priv*,void const*,void*,int,unsigned int) ; 
 int sh_msiof_spi_start (struct sh_msiof_spi_priv*,void*) ; 
 int sh_msiof_spi_stop (struct sh_msiof_spi_priv*,void*) ; 
 int sh_msiof_wait_for_completion (struct sh_msiof_spi_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_msiof_write (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sh_msiof_dma_once(struct sh_msiof_spi_priv *p, const void *tx,
			     void *rx, unsigned int len)
{
	u32 ier_bits = 0;
	struct dma_async_tx_descriptor *desc_tx = NULL, *desc_rx = NULL;
	dma_cookie_t cookie;
	int ret;

	/* First prepare and submit the DMA request(s), as this may fail */
	if (rx) {
		ier_bits |= IER_RDREQE | IER_RDMAE;
		desc_rx = dmaengine_prep_slave_single(p->ctlr->dma_rx,
					p->rx_dma_addr, len, DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		if (!desc_rx)
			return -EAGAIN;

		desc_rx->callback = sh_msiof_dma_complete;
		desc_rx->callback_param = &p->done;
		cookie = dmaengine_submit(desc_rx);
		if (dma_submit_error(cookie))
			return cookie;
	}

	if (tx) {
		ier_bits |= IER_TDREQE | IER_TDMAE;
		dma_sync_single_for_device(p->ctlr->dma_tx->device->dev,
					   p->tx_dma_addr, len, DMA_TO_DEVICE);
		desc_tx = dmaengine_prep_slave_single(p->ctlr->dma_tx,
					p->tx_dma_addr, len, DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		if (!desc_tx) {
			ret = -EAGAIN;
			goto no_dma_tx;
		}

		desc_tx->callback = sh_msiof_dma_complete;
		desc_tx->callback_param = &p->done_txdma;
		cookie = dmaengine_submit(desc_tx);
		if (dma_submit_error(cookie)) {
			ret = cookie;
			goto no_dma_tx;
		}
	}

	/* 1 stage FIFO watermarks for DMA */
	sh_msiof_write(p, FCTR, FCTR_TFWM_1 | FCTR_RFWM_1);

	/* setup msiof transfer mode registers (32-bit words) */
	sh_msiof_spi_set_mode_regs(p, tx, rx, 32, len / 4);

	sh_msiof_write(p, IER, ier_bits);

	reinit_completion(&p->done);
	if (tx)
		reinit_completion(&p->done_txdma);
	p->slave_aborted = false;

	/* Now start DMA */
	if (rx)
		dma_async_issue_pending(p->ctlr->dma_rx);
	if (tx)
		dma_async_issue_pending(p->ctlr->dma_tx);

	ret = sh_msiof_spi_start(p, rx);
	if (ret) {
		dev_err(&p->pdev->dev, "failed to start hardware\n");
		goto stop_dma;
	}

	if (tx) {
		/* wait for tx DMA completion */
		ret = sh_msiof_wait_for_completion(p, &p->done_txdma);
		if (ret)
			goto stop_reset;
	}

	if (rx) {
		/* wait for rx DMA completion */
		ret = sh_msiof_wait_for_completion(p, &p->done);
		if (ret)
			goto stop_reset;

		sh_msiof_write(p, IER, 0);
	} else {
		/* wait for tx fifo to be emptied */
		sh_msiof_write(p, IER, IER_TEOFE);
		ret = sh_msiof_wait_for_completion(p, &p->done);
		if (ret)
			goto stop_reset;
	}

	/* clear status bits */
	sh_msiof_reset_str(p);

	ret = sh_msiof_spi_stop(p, rx);
	if (ret) {
		dev_err(&p->pdev->dev, "failed to shut down hardware\n");
		return ret;
	}

	if (rx)
		dma_sync_single_for_cpu(p->ctlr->dma_rx->device->dev,
					p->rx_dma_addr, len, DMA_FROM_DEVICE);

	return 0;

stop_reset:
	sh_msiof_reset_str(p);
	sh_msiof_spi_stop(p, rx);
stop_dma:
	if (tx)
		dmaengine_terminate_all(p->ctlr->dma_tx);
no_dma_tx:
	if (rx)
		dmaengine_terminate_all(p->ctlr->dma_rx);
	sh_msiof_write(p, IER, 0);
	return ret;
}