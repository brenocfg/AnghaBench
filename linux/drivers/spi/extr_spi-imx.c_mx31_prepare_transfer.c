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
struct spi_transfer {int /*<<< orphan*/  speed_hz; } ;
struct spi_imx_data {unsigned int spi_bus_clk; int bits_per_word; scalar_t__ base; scalar_t__ usedma; int /*<<< orphan*/  spi_clk; } ;
struct spi_device {int mode; unsigned int chip_select; int /*<<< orphan*/  cs_gpio; } ;

/* Variables and functions */
 int MX31_CSPICTRL_BC_SHIFT ; 
 unsigned int MX31_CSPICTRL_CS_SHIFT ; 
 unsigned int MX31_CSPICTRL_DR_SHIFT ; 
 unsigned int MX31_CSPICTRL_ENABLE ; 
 unsigned int MX31_CSPICTRL_MASTER ; 
 unsigned int MX31_CSPICTRL_PHA ; 
 unsigned int MX31_CSPICTRL_POL ; 
 unsigned int MX31_CSPICTRL_SMC ; 
 unsigned int MX31_CSPICTRL_SSCTL ; 
 unsigned int MX31_CSPICTRL_SSPOL ; 
 scalar_t__ MX31_CSPI_DMAREG ; 
 scalar_t__ MX31_CSPI_TESTREG ; 
 unsigned int MX31_DMAREG_RH_DEN ; 
 unsigned int MX31_DMAREG_TH_DEN ; 
 unsigned int MX31_TEST_LBC ; 
 int MX35_CSPICTRL_BL_SHIFT ; 
 unsigned int MX35_CSPICTRL_CS_SHIFT ; 
 scalar_t__ MXC_CSPICTRL ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LOOP ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ is_imx35_cspi (struct spi_imx_data*) ; 
 unsigned int readl (scalar_t__) ; 
 unsigned int spi_imx_clkdiv_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int mx31_prepare_transfer(struct spi_imx_data *spi_imx,
				 struct spi_device *spi,
				 struct spi_transfer *t)
{
	unsigned int reg = MX31_CSPICTRL_ENABLE | MX31_CSPICTRL_MASTER;
	unsigned int clk;

	reg |= spi_imx_clkdiv_2(spi_imx->spi_clk, t->speed_hz, &clk) <<
		MX31_CSPICTRL_DR_SHIFT;
	spi_imx->spi_bus_clk = clk;

	if (is_imx35_cspi(spi_imx)) {
		reg |= (spi_imx->bits_per_word - 1) << MX35_CSPICTRL_BL_SHIFT;
		reg |= MX31_CSPICTRL_SSCTL;
	} else {
		reg |= (spi_imx->bits_per_word - 1) << MX31_CSPICTRL_BC_SHIFT;
	}

	if (spi->mode & SPI_CPHA)
		reg |= MX31_CSPICTRL_PHA;
	if (spi->mode & SPI_CPOL)
		reg |= MX31_CSPICTRL_POL;
	if (spi->mode & SPI_CS_HIGH)
		reg |= MX31_CSPICTRL_SSPOL;
	if (!gpio_is_valid(spi->cs_gpio))
		reg |= (spi->chip_select) <<
			(is_imx35_cspi(spi_imx) ? MX35_CSPICTRL_CS_SHIFT :
						  MX31_CSPICTRL_CS_SHIFT);

	if (spi_imx->usedma)
		reg |= MX31_CSPICTRL_SMC;

	writel(reg, spi_imx->base + MXC_CSPICTRL);

	reg = readl(spi_imx->base + MX31_CSPI_TESTREG);
	if (spi->mode & SPI_LOOP)
		reg |= MX31_TEST_LBC;
	else
		reg &= ~MX31_TEST_LBC;
	writel(reg, spi_imx->base + MX31_CSPI_TESTREG);

	if (spi_imx->usedma) {
		/*
		 * configure DMA requests when RXFIFO is half full and
		 * when TXFIFO is half empty
		 */
		writel(MX31_DMAREG_RH_DEN | MX31_DMAREG_TH_DEN,
			spi_imx->base + MX31_CSPI_DMAREG);
	}

	return 0;
}