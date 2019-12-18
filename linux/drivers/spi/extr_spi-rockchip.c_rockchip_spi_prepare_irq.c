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
struct spi_transfer {int len; int /*<<< orphan*/  rx_buf; scalar_t__ tx_buf; } ;
struct rockchip_spi {int tx_left; int n_bytes; int rx_left; scalar_t__ regs; scalar_t__ tx; int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_RF_FULL ; 
 scalar_t__ ROCKCHIP_SPI_IMR ; 
 int /*<<< orphan*/  rockchip_spi_pio_writer (struct rockchip_spi*) ; 
 int /*<<< orphan*/  spi_enable_chip (struct rockchip_spi*,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rockchip_spi_prepare_irq(struct rockchip_spi *rs,
		struct spi_transfer *xfer)
{
	rs->tx = xfer->tx_buf;
	rs->rx = xfer->rx_buf;
	rs->tx_left = rs->tx ? xfer->len / rs->n_bytes : 0;
	rs->rx_left = xfer->len / rs->n_bytes;

	writel_relaxed(INT_RF_FULL, rs->regs + ROCKCHIP_SPI_IMR);
	spi_enable_chip(rs, true);

	if (rs->tx_left)
		rockchip_spi_pio_writer(rs);

	/* 1 means the transfer is in progress */
	return 1;
}