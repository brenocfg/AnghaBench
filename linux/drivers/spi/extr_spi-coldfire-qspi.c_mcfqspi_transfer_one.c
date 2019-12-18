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
typedef  int u16 ;
struct spi_transfer {int bits_per_word; int len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  speed_hz; } ;
struct spi_master {int dummy; } ;
struct spi_device {int mode; } ;
struct mcfqspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCFQSPI_QIR_SPIFE ; 
 int MCFQSPI_QMR_CPHA ; 
 int MCFQSPI_QMR_CPOL ; 
 int MCFQSPI_QMR_MSTR ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int mcfqspi_qmr_baud (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcfqspi_transfer_msg16 (struct mcfqspi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcfqspi_transfer_msg8 (struct mcfqspi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcfqspi_wr_qir (struct mcfqspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcfqspi_wr_qmr (struct mcfqspi*,int) ; 
 struct mcfqspi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int mcfqspi_transfer_one(struct spi_master *master,
				struct spi_device *spi,
				struct spi_transfer *t)
{
	struct mcfqspi *mcfqspi = spi_master_get_devdata(master);
	u16 qmr = MCFQSPI_QMR_MSTR;

	qmr |= t->bits_per_word << 10;
	if (spi->mode & SPI_CPHA)
		qmr |= MCFQSPI_QMR_CPHA;
	if (spi->mode & SPI_CPOL)
		qmr |= MCFQSPI_QMR_CPOL;
	qmr |= mcfqspi_qmr_baud(t->speed_hz);
	mcfqspi_wr_qmr(mcfqspi, qmr);

	mcfqspi_wr_qir(mcfqspi, MCFQSPI_QIR_SPIFE);
	if (t->bits_per_word == 8)
		mcfqspi_transfer_msg8(mcfqspi, t->len, t->tx_buf, t->rx_buf);
	else
		mcfqspi_transfer_msg16(mcfqspi, t->len / 2, t->tx_buf,
				       t->rx_buf);
	mcfqspi_wr_qir(mcfqspi, 0);

	return 0;
}