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
struct spi_device {int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int CFG_IOPADMODE_MASK ; 
 int CFG_SCLKCNT (int) ; 
 int CFG_SPI_3W4WB (int) ; 
 int CFG_SPI_ENA (int) ; 
 int CFG_SPI_SEL (int) ; 
 int CFG_TXBITS (int /*<<< orphan*/ ) ; 
 int IOPAD_DUMB18SPI ; 
 int LCD_SPU_SPI_CTRL ; 
 int SPU_IOPAD_CONTROL ; 
 int readl_relaxed (void*) ; 
 scalar_t__ spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,void*) ; 
 int /*<<< orphan*/  writel_relaxed (int,void*) ; 

__attribute__((used)) static int lcd_spi_setup(struct spi_device *spi)
{
	void *reg_base =
		*(void **)spi_master_get_devdata(spi->master);
	u32 tmp;

	tmp = CFG_SCLKCNT(16) |
		CFG_TXBITS(spi->bits_per_word) |
		CFG_SPI_SEL(1) | CFG_SPI_ENA(1) |
		CFG_SPI_3W4WB(1);
	writel(tmp, reg_base + LCD_SPU_SPI_CTRL);

	/*
	 * After set mode it need a time to pull up the spi singals,
	 * or it would cause the wrong waveform when send spi command,
	 * especially on pxa910h
	 */
	tmp = readl_relaxed(reg_base + SPU_IOPAD_CONTROL);
	if ((tmp & CFG_IOPADMODE_MASK) != IOPAD_DUMB18SPI)
		writel_relaxed(IOPAD_DUMB18SPI |
			(tmp & ~CFG_IOPADMODE_MASK),
			reg_base + SPU_IOPAD_CONTROL);
	udelay(20);
	return 0;
}