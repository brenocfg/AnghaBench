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
struct tegra_spi_data {int cur_direction; scalar_t__ cur_pos; scalar_t__ cur_tx_pos; scalar_t__ cur_rx_pos; int /*<<< orphan*/  lock; int /*<<< orphan*/  cur_spi; int /*<<< orphan*/  xfer_completion; int /*<<< orphan*/  rst; int /*<<< orphan*/  dma_control_reg; int /*<<< orphan*/  command1_reg; int /*<<< orphan*/  dev; int /*<<< orphan*/  status_reg; scalar_t__ rx_status; scalar_t__ tx_status; struct spi_transfer* curr_xfer; } ;
struct spi_transfer {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DATA_DIR_RX ; 
 int DATA_DIR_TX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_spi_calculate_curr_xfer_param (int /*<<< orphan*/ ,struct tegra_spi_data*,struct spi_transfer*) ; 
 int /*<<< orphan*/  tegra_spi_dump_regs (struct tegra_spi_data*) ; 
 int /*<<< orphan*/  tegra_spi_flush_fifos (struct tegra_spi_data*) ; 
 int /*<<< orphan*/  tegra_spi_read_rx_fifo_to_client_rxbuf (struct tegra_spi_data*,struct spi_transfer*) ; 
 int /*<<< orphan*/  tegra_spi_start_cpu_based_transfer (struct tegra_spi_data*,struct spi_transfer*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static irqreturn_t handle_cpu_based_xfer(struct tegra_spi_data *tspi)
{
	struct spi_transfer *t = tspi->curr_xfer;
	unsigned long flags;

	spin_lock_irqsave(&tspi->lock, flags);
	if (tspi->tx_status ||  tspi->rx_status) {
		dev_err(tspi->dev, "CpuXfer ERROR bit set 0x%x\n",
			tspi->status_reg);
		dev_err(tspi->dev, "CpuXfer 0x%08x:0x%08x\n",
			tspi->command1_reg, tspi->dma_control_reg);
		tegra_spi_dump_regs(tspi);
		tegra_spi_flush_fifos(tspi);
		complete(&tspi->xfer_completion);
		spin_unlock_irqrestore(&tspi->lock, flags);
		reset_control_assert(tspi->rst);
		udelay(2);
		reset_control_deassert(tspi->rst);
		return IRQ_HANDLED;
	}

	if (tspi->cur_direction & DATA_DIR_RX)
		tegra_spi_read_rx_fifo_to_client_rxbuf(tspi, t);

	if (tspi->cur_direction & DATA_DIR_TX)
		tspi->cur_pos = tspi->cur_tx_pos;
	else
		tspi->cur_pos = tspi->cur_rx_pos;

	if (tspi->cur_pos == t->len) {
		complete(&tspi->xfer_completion);
		goto exit;
	}

	tegra_spi_calculate_curr_xfer_param(tspi->cur_spi, tspi, t);
	tegra_spi_start_cpu_based_transfer(tspi, t);
exit:
	spin_unlock_irqrestore(&tspi->lock, flags);
	return IRQ_HANDLED;
}