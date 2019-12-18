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
struct spi_transfer {int /*<<< orphan*/  len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_device {int /*<<< orphan*/  master; int /*<<< orphan*/  dev; } ;
struct ppc4xx_spi {int count; int /*<<< orphan*/  done; TYPE_1__* regs; int /*<<< orphan*/ * tx; int /*<<< orphan*/  len; int /*<<< orphan*/  rx; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr; int /*<<< orphan*/  txd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_PPC4XX_CR_STR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ppc4xx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spi_ppc4xx_txrx(struct spi_device *spi, struct spi_transfer *t)
{
	struct ppc4xx_spi *hw;
	u8 data;

	dev_dbg(&spi->dev, "txrx: tx %p, rx %p, len %d\n",
		t->tx_buf, t->rx_buf, t->len);

	hw = spi_master_get_devdata(spi->master);

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	hw->len = t->len;
	hw->count = 0;

	/* send the first byte */
	data = hw->tx ? hw->tx[0] : 0;
	out_8(&hw->regs->txd, data);
	out_8(&hw->regs->cr, SPI_PPC4XX_CR_STR);
	wait_for_completion(&hw->done);

	return hw->count;
}