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
typedef  int u32 ;
struct spi_transfer {int speed_hz; } ;
struct spi_master {int dummy; } ;
struct mtk_spi {scalar_t__ base; TYPE_1__* dev_comp; int /*<<< orphan*/  spi_clk; } ;
struct TYPE_2__ {scalar_t__ enhance_timing; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int SPI_ADJUST_CFG0_CS_HOLD_OFFSET ; 
 int SPI_ADJUST_CFG0_CS_SETUP_OFFSET ; 
 int SPI_ADJUST_CFG0_SCK_LOW_OFFSET ; 
 int SPI_CFG0_CS_HOLD_OFFSET ; 
 int SPI_CFG0_CS_SETUP_OFFSET ; 
 scalar_t__ SPI_CFG0_REG ; 
 int SPI_CFG0_SCK_HIGH_OFFSET ; 
 int SPI_CFG0_SCK_LOW_OFFSET ; 
 int SPI_CFG1_CS_IDLE_MASK ; 
 int SPI_CFG1_CS_IDLE_OFFSET ; 
 scalar_t__ SPI_CFG1_REG ; 
 scalar_t__ SPI_CFG2_REG ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct mtk_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_spi_prepare_transfer(struct spi_master *master,
				     struct spi_transfer *xfer)
{
	u32 spi_clk_hz, div, sck_time, cs_time, reg_val = 0;
	struct mtk_spi *mdata = spi_master_get_devdata(master);

	spi_clk_hz = clk_get_rate(mdata->spi_clk);
	if (xfer->speed_hz < spi_clk_hz / 2)
		div = DIV_ROUND_UP(spi_clk_hz, xfer->speed_hz);
	else
		div = 1;

	sck_time = (div + 1) / 2;
	cs_time = sck_time * 2;

	if (mdata->dev_comp->enhance_timing) {
		reg_val |= (((sck_time - 1) & 0xffff)
			   << SPI_CFG0_SCK_HIGH_OFFSET);
		reg_val |= (((sck_time - 1) & 0xffff)
			   << SPI_ADJUST_CFG0_SCK_LOW_OFFSET);
		writel(reg_val, mdata->base + SPI_CFG2_REG);
		reg_val |= (((cs_time - 1) & 0xffff)
			   << SPI_ADJUST_CFG0_CS_HOLD_OFFSET);
		reg_val |= (((cs_time - 1) & 0xffff)
			   << SPI_ADJUST_CFG0_CS_SETUP_OFFSET);
		writel(reg_val, mdata->base + SPI_CFG0_REG);
	} else {
		reg_val |= (((sck_time - 1) & 0xff)
			   << SPI_CFG0_SCK_HIGH_OFFSET);
		reg_val |= (((sck_time - 1) & 0xff) << SPI_CFG0_SCK_LOW_OFFSET);
		reg_val |= (((cs_time - 1) & 0xff) << SPI_CFG0_CS_HOLD_OFFSET);
		reg_val |= (((cs_time - 1) & 0xff) << SPI_CFG0_CS_SETUP_OFFSET);
		writel(reg_val, mdata->base + SPI_CFG0_REG);
	}

	reg_val = readl(mdata->base + SPI_CFG1_REG);
	reg_val &= ~SPI_CFG1_CS_IDLE_MASK;
	reg_val |= (((cs_time - 1) & 0xff) << SPI_CFG1_CS_IDLE_OFFSET);
	writel(reg_val, mdata->base + SPI_CFG1_REG);
}