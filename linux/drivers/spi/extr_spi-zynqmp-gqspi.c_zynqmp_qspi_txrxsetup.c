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
typedef  int /*<<< orphan*/  u32 ;
struct zynqmp_qspi {scalar_t__ mode; scalar_t__ bytes_to_receive; scalar_t__ bytes_to_transfer; int /*<<< orphan*/ * rxbuf; int /*<<< orphan*/ * txbuf; } ;
struct spi_transfer {scalar_t__ len; int /*<<< orphan*/  rx_nbits; int /*<<< orphan*/  tx_nbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  GQSPI_CFG_MODE_EN_MASK ; 
 int /*<<< orphan*/  GQSPI_CONFIG_OFST ; 
 int /*<<< orphan*/  GQSPI_GENFIFO_DATA_XFER ; 
 int /*<<< orphan*/  GQSPI_GENFIFO_RX ; 
 int /*<<< orphan*/  GQSPI_GENFIFO_TX ; 
 scalar_t__ GQSPI_MODE_DMA ; 
 scalar_t__ GQSPI_MODE_IO ; 
 int /*<<< orphan*/  GQSPI_TXD_DEPTH ; 
 int /*<<< orphan*/  zynq_qspi_setuprxdma (struct zynqmp_qspi*) ; 
 int /*<<< orphan*/  zynqmp_gqspi_read (struct zynqmp_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_gqspi_write (struct zynqmp_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_qspi_filltxfifo (struct zynqmp_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_qspi_selectspimode (struct zynqmp_qspi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zynqmp_qspi_txrxsetup(struct zynqmp_qspi *xqspi,
				  struct spi_transfer *transfer,
				  u32 *genfifoentry)
{
	u32 config_reg;

	/* Transmit */
	if ((xqspi->txbuf != NULL) && (xqspi->rxbuf == NULL)) {
		/* Setup data to be TXed */
		*genfifoentry &= ~GQSPI_GENFIFO_RX;
		*genfifoentry |= GQSPI_GENFIFO_DATA_XFER;
		*genfifoentry |= GQSPI_GENFIFO_TX;
		*genfifoentry |=
			zynqmp_qspi_selectspimode(xqspi, transfer->tx_nbits);
		xqspi->bytes_to_transfer = transfer->len;
		if (xqspi->mode == GQSPI_MODE_DMA) {
			config_reg = zynqmp_gqspi_read(xqspi,
							GQSPI_CONFIG_OFST);
			config_reg &= ~GQSPI_CFG_MODE_EN_MASK;
			zynqmp_gqspi_write(xqspi, GQSPI_CONFIG_OFST,
								config_reg);
			xqspi->mode = GQSPI_MODE_IO;
		}
		zynqmp_qspi_filltxfifo(xqspi, GQSPI_TXD_DEPTH);
		/* Discard RX data */
		xqspi->bytes_to_receive = 0;
	} else if ((xqspi->txbuf == NULL) && (xqspi->rxbuf != NULL)) {
		/* Receive */

		/* TX auto fill */
		*genfifoentry &= ~GQSPI_GENFIFO_TX;
		/* Setup RX */
		*genfifoentry |= GQSPI_GENFIFO_DATA_XFER;
		*genfifoentry |= GQSPI_GENFIFO_RX;
		*genfifoentry |=
			zynqmp_qspi_selectspimode(xqspi, transfer->rx_nbits);
		xqspi->bytes_to_transfer = 0;
		xqspi->bytes_to_receive = transfer->len;
		zynq_qspi_setuprxdma(xqspi);
	}
}