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
struct tegra_spi_data {int command1_reg; int /*<<< orphan*/  def_command1_reg; int /*<<< orphan*/  dev; int /*<<< orphan*/  cur_direction; scalar_t__ is_packed; } ;
struct spi_transfer {scalar_t__ rx_nbits; scalar_t__ tx_nbits; scalar_t__ tx_buf; scalar_t__ rx_buf; } ;
struct spi_device {int /*<<< orphan*/  chip_select; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_DIR_RX ; 
 int /*<<< orphan*/  DATA_DIR_TX ; 
 int SPI_BOTH_EN_BIT ; 
 int /*<<< orphan*/  SPI_COMMAND1 ; 
 int SPI_CS_SEL (int /*<<< orphan*/ ) ; 
 int SPI_CS_SEL_MASK ; 
 unsigned int SPI_FIFO_DEPTH ; 
 scalar_t__ SPI_NBITS_DUAL ; 
 int SPI_PACKED ; 
 int SPI_RX_EN ; 
 int SPI_TX_EN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct tegra_spi_data* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 unsigned int tegra_spi_calculate_curr_xfer_param (struct spi_device*,struct tegra_spi_data*,struct spi_transfer*) ; 
 int tegra_spi_flush_fifos (struct tegra_spi_data*) ; 
 int tegra_spi_start_cpu_based_transfer (struct tegra_spi_data*,struct spi_transfer*) ; 
 int tegra_spi_start_dma_based_transfer (struct tegra_spi_data*,struct spi_transfer*) ; 
 int /*<<< orphan*/  tegra_spi_writel (struct tegra_spi_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_spi_start_transfer_one(struct spi_device *spi,
		struct spi_transfer *t, u32 command1)
{
	struct tegra_spi_data *tspi = spi_master_get_devdata(spi->master);
	unsigned total_fifo_words;
	int ret;

	total_fifo_words = tegra_spi_calculate_curr_xfer_param(spi, tspi, t);

	if (t->rx_nbits == SPI_NBITS_DUAL || t->tx_nbits == SPI_NBITS_DUAL)
		command1 |= SPI_BOTH_EN_BIT;
	else
		command1 &= ~SPI_BOTH_EN_BIT;

	if (tspi->is_packed)
		command1 |= SPI_PACKED;
	else
		command1 &= ~SPI_PACKED;

	command1 &= ~(SPI_CS_SEL_MASK | SPI_TX_EN | SPI_RX_EN);
	tspi->cur_direction = 0;
	if (t->rx_buf) {
		command1 |= SPI_RX_EN;
		tspi->cur_direction |= DATA_DIR_RX;
	}
	if (t->tx_buf) {
		command1 |= SPI_TX_EN;
		tspi->cur_direction |= DATA_DIR_TX;
	}
	command1 |= SPI_CS_SEL(spi->chip_select);
	tegra_spi_writel(tspi, command1, SPI_COMMAND1);
	tspi->command1_reg = command1;

	dev_dbg(tspi->dev, "The def 0x%x and written 0x%x\n",
		tspi->def_command1_reg, (unsigned)command1);

	ret = tegra_spi_flush_fifos(tspi);
	if (ret < 0)
		return ret;
	if (total_fifo_words > SPI_FIFO_DEPTH)
		ret = tegra_spi_start_dma_based_transfer(tspi, t);
	else
		ret = tegra_spi_start_cpu_based_transfer(tspi, t);
	return ret;
}