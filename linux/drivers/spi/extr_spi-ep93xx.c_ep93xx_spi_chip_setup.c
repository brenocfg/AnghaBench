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
typedef  int u8 ;
typedef  int u16 ;
struct spi_transfer {int /*<<< orphan*/  speed_hz; int /*<<< orphan*/  bits_per_word; } ;
struct spi_master {int /*<<< orphan*/  dev; } ;
struct spi_device {int mode; } ;
struct ep93xx_spi {scalar_t__ mmio; } ;

/* Variables and functions */
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 scalar_t__ SSPCPSR ; 
 scalar_t__ SSPCR0 ; 
 int SSPCR0_MODE_SHIFT ; 
 int SSPCR0_SCR_SHIFT ; 
 int bits_per_word_to_dss (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int ep93xx_spi_calc_divisors (struct spi_master*,int /*<<< orphan*/ ,int*,int*) ; 
 struct ep93xx_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ep93xx_spi_chip_setup(struct spi_master *master,
				 struct spi_device *spi,
				 struct spi_transfer *xfer)
{
	struct ep93xx_spi *espi = spi_master_get_devdata(master);
	u8 dss = bits_per_word_to_dss(xfer->bits_per_word);
	u8 div_cpsr = 0;
	u8 div_scr = 0;
	u16 cr0;
	int err;

	err = ep93xx_spi_calc_divisors(master, xfer->speed_hz,
				       &div_cpsr, &div_scr);
	if (err)
		return err;

	cr0 = div_scr << SSPCR0_SCR_SHIFT;
	cr0 |= (spi->mode & (SPI_CPHA | SPI_CPOL)) << SSPCR0_MODE_SHIFT;
	cr0 |= dss;

	dev_dbg(&master->dev, "setup: mode %d, cpsr %d, scr %d, dss %d\n",
		spi->mode, div_cpsr, div_scr, dss);
	dev_dbg(&master->dev, "setup: cr0 %#x\n", cr0);

	writel(div_cpsr, espi->mmio + SSPCPSR);
	writel(cr0, espi->mmio + SSPCR0);

	return 0;
}