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
struct spi_transfer {scalar_t__ len; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct spi_controller {int dummy; } ;
struct at91_usart_spi {int xfer_failed; int /*<<< orphan*/ * dev; scalar_t__ current_tx_remaining_bytes; int /*<<< orphan*/  xfer_completion; scalar_t__ current_rx_remaining_bytes; struct spi_transfer* current_transfer; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ at91_usart_spi_can_dma (struct spi_controller*,struct spi_device*,struct spi_transfer*) ; 
 unsigned long at91_usart_spi_dma_timeout (struct at91_usart_spi*) ; 
 int at91_usart_spi_dma_transfer (struct spi_controller*,struct spi_transfer*) ; 
 int /*<<< orphan*/  at91_usart_spi_read_status (struct at91_usart_spi*) ; 
 int /*<<< orphan*/  at91_usart_spi_set_xfer_speed (struct at91_usart_spi*,struct spi_transfer*) ; 
 int /*<<< orphan*/  at91_usart_spi_tx (struct at91_usart_spi*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct at91_usart_spi* spi_master_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int at91_usart_spi_transfer_one(struct spi_controller *ctlr,
				       struct spi_device *spi,
				       struct spi_transfer *xfer)
{
	struct at91_usart_spi *aus = spi_master_get_devdata(ctlr);
	unsigned long dma_timeout = 0;
	int ret = 0;

	at91_usart_spi_set_xfer_speed(aus, xfer);
	aus->xfer_failed = false;
	aus->current_transfer = xfer;
	aus->current_tx_remaining_bytes = xfer->len;
	aus->current_rx_remaining_bytes = xfer->len;

	while ((aus->current_tx_remaining_bytes ||
		aus->current_rx_remaining_bytes) && !aus->xfer_failed) {
		reinit_completion(&aus->xfer_completion);
		if (at91_usart_spi_can_dma(ctlr, spi, xfer) &&
		    !ret) {
			ret = at91_usart_spi_dma_transfer(ctlr, xfer);
			if (ret)
				continue;

			dma_timeout = at91_usart_spi_dma_timeout(aus);

			if (WARN_ON(dma_timeout == 0)) {
				dev_err(&spi->dev, "DMA transfer timeout\n");
				return -EIO;
			}
			aus->current_tx_remaining_bytes = 0;
		} else {
			at91_usart_spi_read_status(aus);
			at91_usart_spi_tx(aus);
		}

		cpu_relax();
	}

	if (aus->xfer_failed) {
		dev_err(aus->dev, "Overrun!\n");
		return -EIO;
	}

	return 0;
}