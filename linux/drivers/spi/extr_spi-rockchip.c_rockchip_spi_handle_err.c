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
struct spi_message {int dummy; } ;
struct spi_master {int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  dma_tx; } ;
struct rockchip_spi {int /*<<< orphan*/  state; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ROCKCHIP_SPI_IMR ; 
 int RXDMA ; 
 int TXDMA ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_terminate_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_enable_chip (struct rockchip_spi*,int) ; 
 struct rockchip_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rockchip_spi_handle_err(struct spi_master *master,
				    struct spi_message *msg)
{
	struct rockchip_spi *rs = spi_master_get_devdata(master);

	/* stop running spi transfer
	 * this also flushes both rx and tx fifos
	 */
	spi_enable_chip(rs, false);

	/* make sure all interrupts are masked */
	writel_relaxed(0, rs->regs + ROCKCHIP_SPI_IMR);

	if (atomic_read(&rs->state) & TXDMA)
		dmaengine_terminate_async(master->dma_tx);

	if (atomic_read(&rs->state) & RXDMA)
		dmaengine_terminate_async(master->dma_rx);
}