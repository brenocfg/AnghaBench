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
struct tegra_spi_data {int /*<<< orphan*/  def_command1_reg; int /*<<< orphan*/  command1_reg; int /*<<< orphan*/  use_hw_based_cs; } ;
struct spi_device {int mode; scalar_t__ cs_gpiod; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_COMMAND1 ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  SPI_CS_SW_VAL ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 struct tegra_spi_data* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_spi_writel (struct tegra_spi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_spi_transfer_end(struct spi_device *spi)
{
	struct tegra_spi_data *tspi = spi_master_get_devdata(spi->master);
	int cs_val = (spi->mode & SPI_CS_HIGH) ? 0 : 1;

	/* GPIO based chip select control */
	if (spi->cs_gpiod)
		gpiod_set_value(spi->cs_gpiod, 0);

	if (!tspi->use_hw_based_cs) {
		if (cs_val)
			tspi->command1_reg |= SPI_CS_SW_VAL;
		else
			tspi->command1_reg &= ~SPI_CS_SW_VAL;
		tegra_spi_writel(tspi, tspi->command1_reg, SPI_COMMAND1);
	}

	tegra_spi_writel(tspi, tspi->def_command1_reg, SPI_COMMAND1);
}