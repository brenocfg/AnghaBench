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
struct tegra_spi_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long HZ ; 
 int SPI_FIFO_EMPTY ; 
 int /*<<< orphan*/  SPI_FIFO_STATUS ; 
 int SPI_RX_FIFO_FLUSH ; 
 int SPI_TX_FIFO_FLUSH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int tegra_spi_readl (struct tegra_spi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_spi_writel (struct tegra_spi_data*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tegra_spi_flush_fifos(struct tegra_spi_data *tspi)
{
	unsigned long timeout = jiffies + HZ;
	u32 status;

	status = tegra_spi_readl(tspi, SPI_FIFO_STATUS);
	if ((status & SPI_FIFO_EMPTY) != SPI_FIFO_EMPTY) {
		status |= SPI_RX_FIFO_FLUSH | SPI_TX_FIFO_FLUSH;
		tegra_spi_writel(tspi, status, SPI_FIFO_STATUS);
		while ((status & SPI_FIFO_EMPTY) != SPI_FIFO_EMPTY) {
			status = tegra_spi_readl(tspi, SPI_FIFO_STATUS);
			if (time_after(jiffies, timeout)) {
				dev_err(tspi->dev,
					"timeout waiting for fifo flush\n");
				return -EIO;
			}

			udelay(1);
		}
	}

	return 0;
}