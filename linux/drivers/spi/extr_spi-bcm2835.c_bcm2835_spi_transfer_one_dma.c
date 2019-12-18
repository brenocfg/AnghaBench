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
typedef  int u32 ;
struct spi_transfer {int dummy; } ;
struct spi_device {size_t chip_select; } ;
struct spi_controller {int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  dma_tx; } ;
struct bcm2835_spi {int tx_len; int tx_dma_active; int rx_dma_active; scalar_t__ rx_buf; int /*<<< orphan*/ * clear_rx_desc; int /*<<< orphan*/  fill_tx_desc; scalar_t__ tx_buf; int /*<<< orphan*/  count_transfer_dma; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_DMAEN ; 
 int BCM2835_SPI_CS_TA ; 
 int /*<<< orphan*/  BCM2835_SPI_DLEN ; 
 int bcm2835_spi_prepare_sg (struct spi_controller*,struct spi_device*,struct spi_transfer*,struct bcm2835_spi*,int) ; 
 int /*<<< orphan*/  bcm2835_spi_reset_hw (struct spi_controller*) ; 
 int /*<<< orphan*/  bcm2835_spi_transfer_prologue (struct spi_controller*,struct spi_transfer*,struct bcm2835_spi*,int) ; 
 int /*<<< orphan*/  bcm2835_spi_undo_prologue (struct bcm2835_spi*) ; 
 int /*<<< orphan*/  bcm2835_wr (struct bcm2835_spi*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cmpxchg (int*,int,int) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 struct bcm2835_spi* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int bcm2835_spi_transfer_one_dma(struct spi_controller *ctlr,
					struct spi_device *spi,
					struct spi_transfer *tfr,
					u32 cs)
{
	struct bcm2835_spi *bs = spi_controller_get_devdata(ctlr);
	dma_cookie_t cookie;
	int ret;

	/* update usage statistics */
	bs->count_transfer_dma++;

	/*
	 * Transfer first few bytes without DMA if length of first TX or RX
	 * sglist entry is not a multiple of 4 bytes (hardware limitation).
	 */
	bcm2835_spi_transfer_prologue(ctlr, tfr, bs, cs);

	/* setup tx-DMA */
	if (bs->tx_buf) {
		ret = bcm2835_spi_prepare_sg(ctlr, spi, tfr, bs, true);
	} else {
		cookie = dmaengine_submit(bs->fill_tx_desc);
		ret = dma_submit_error(cookie);
	}
	if (ret)
		goto err_reset_hw;

	/* set the DMA length */
	bcm2835_wr(bs, BCM2835_SPI_DLEN, bs->tx_len);

	/* start the HW */
	bcm2835_wr(bs, BCM2835_SPI_CS,
		   cs | BCM2835_SPI_CS_TA | BCM2835_SPI_CS_DMAEN);

	bs->tx_dma_active = true;
	smp_wmb();

	/* start TX early */
	dma_async_issue_pending(ctlr->dma_tx);

	/* setup rx-DMA late - to run transfers while
	 * mapping of the rx buffers still takes place
	 * this saves 10us or more.
	 */
	if (bs->rx_buf) {
		ret = bcm2835_spi_prepare_sg(ctlr, spi, tfr, bs, false);
	} else {
		cookie = dmaengine_submit(bs->clear_rx_desc[spi->chip_select]);
		ret = dma_submit_error(cookie);
	}
	if (ret) {
		/* need to reset on errors */
		dmaengine_terminate_sync(ctlr->dma_tx);
		bs->tx_dma_active = false;
		goto err_reset_hw;
	}

	/* start rx dma late */
	dma_async_issue_pending(ctlr->dma_rx);
	bs->rx_dma_active = true;
	smp_mb();

	/*
	 * In case of a very short TX-only transfer, bcm2835_spi_dma_tx_done()
	 * may run before RX DMA is issued.  Terminate RX DMA if so.
	 */
	if (!bs->rx_buf && !bs->tx_dma_active &&
	    cmpxchg(&bs->rx_dma_active, true, false)) {
		dmaengine_terminate_async(ctlr->dma_rx);
		bcm2835_spi_reset_hw(ctlr);
	}

	/* wait for wakeup in framework */
	return 1;

err_reset_hw:
	bcm2835_spi_reset_hw(ctlr);
	bcm2835_spi_undo_prologue(bs);
	return ret;
}