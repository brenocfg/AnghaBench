#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_4__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct spi_transfer {TYPE_2__ tx_sg; TYPE_1__ rx_sg; } ;
struct spi_controller {struct dma_chan* dma_tx; struct dma_chan* dma_rx; } ;
struct dma_chan {TYPE_3__* device; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  (* tx_submit ) (struct dma_async_tx_descriptor*) ;struct spi_controller* callback_param; int /*<<< orphan*/  callback; } ;
struct at91_usart_spi {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* device_issue_pending ) (struct dma_chan*) ;} ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IDR ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  US_IR_RXRDY ; 
 int /*<<< orphan*/  at91_usart_spi_stop_dma (struct spi_controller*) ; 
 int /*<<< orphan*/  at91_usart_spi_writel (struct at91_usart_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_callback ; 
 scalar_t__ dma_submit_error (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct at91_usart_spi* spi_master_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  stub1 (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  stub2 (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  stub3 (struct dma_chan*) ; 
 int /*<<< orphan*/  stub4 (struct dma_chan*) ; 

__attribute__((used)) static int at91_usart_spi_dma_transfer(struct spi_controller *ctlr,
				       struct spi_transfer *xfer)
{
	struct at91_usart_spi *aus = spi_master_get_devdata(ctlr);
	struct dma_chan	 *rxchan = ctlr->dma_rx;
	struct dma_chan *txchan = ctlr->dma_tx;
	struct dma_async_tx_descriptor *rxdesc;
	struct dma_async_tx_descriptor *txdesc;
	dma_cookie_t cookie;

	/* Disable RX interrupt */
	at91_usart_spi_writel(aus, IDR, US_IR_RXRDY);

	rxdesc = dmaengine_prep_slave_sg(rxchan,
					 xfer->rx_sg.sgl,
					 xfer->rx_sg.nents,
					 DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT |
					 DMA_CTRL_ACK);
	if (!rxdesc)
		goto at91_usart_spi_err_dma;

	txdesc = dmaengine_prep_slave_sg(txchan,
					 xfer->tx_sg.sgl,
					 xfer->tx_sg.nents,
					 DMA_MEM_TO_DEV,
					 DMA_PREP_INTERRUPT |
					 DMA_CTRL_ACK);
	if (!txdesc)
		goto at91_usart_spi_err_dma;

	rxdesc->callback = dma_callback;
	rxdesc->callback_param = ctlr;

	cookie = rxdesc->tx_submit(rxdesc);
	if (dma_submit_error(cookie))
		goto at91_usart_spi_err_dma;

	cookie = txdesc->tx_submit(txdesc);
	if (dma_submit_error(cookie))
		goto at91_usart_spi_err_dma;

	rxchan->device->device_issue_pending(rxchan);
	txchan->device->device_issue_pending(txchan);

	return 0;

at91_usart_spi_err_dma:
	/* Enable RX interrupt if something fails and fallback to PIO */
	at91_usart_spi_writel(aus, IER, US_IR_RXRDY);
	at91_usart_spi_stop_dma(ctlr);

	return -ENOMEM;
}