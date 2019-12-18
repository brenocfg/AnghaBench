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
typedef  unsigned int u32 ;
struct lantiq_ssc_spi {int /*<<< orphan*/  dev; int /*<<< orphan*/  fpi_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_SPI_BRT ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  lantiq_ssc_writel (struct lantiq_ssc_spi const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hw_setup_speed_hz(const struct lantiq_ssc_spi *spi,
			      unsigned int max_speed_hz)
{
	u32 spi_clk, brt;

	/*
	 * SPI module clock is derived from FPI bus clock dependent on
	 * divider value in CLC.RMS which is always set to 1.
	 *
	 *                 f_SPI
	 * baudrate = --------------
	 *             2 * (BR + 1)
	 */
	spi_clk = clk_get_rate(spi->fpi_clk) / 2;

	if (max_speed_hz > spi_clk)
		brt = 0;
	else
		brt = spi_clk / max_speed_hz - 1;

	if (brt > 0xFFFF)
		brt = 0xFFFF;

	dev_dbg(spi->dev, "spi_clk %u, max_speed_hz %u, brt %u\n",
		spi_clk, max_speed_hz, brt);

	lantiq_ssc_writel(spi, brt, LTQ_SPI_BRT);
}