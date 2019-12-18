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
struct tegra_spi_data {int dummy; } ;

/* Variables and functions */
 int SPI_ERR ; 
 int SPI_FIFO_ERROR ; 
 int /*<<< orphan*/  SPI_FIFO_STATUS ; 
 int /*<<< orphan*/  SPI_TRANS_STATUS ; 
 int tegra_spi_readl (struct tegra_spi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_spi_writel (struct tegra_spi_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_spi_clear_status(struct tegra_spi_data *tspi)
{
	u32 val;

	/* Write 1 to clear status register */
	val = tegra_spi_readl(tspi, SPI_TRANS_STATUS);
	tegra_spi_writel(tspi, val, SPI_TRANS_STATUS);

	/* Clear fifo status error if any */
	val = tegra_spi_readl(tspi, SPI_FIFO_STATUS);
	if (val & SPI_ERR)
		tegra_spi_writel(tspi, SPI_ERR | SPI_FIFO_ERROR,
				SPI_FIFO_STATUS);
}