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
struct dw_spi {int fifo_len; scalar_t__ cs_override; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_SPI_CS_OVERRIDE ; 
 int /*<<< orphan*/  DW_SPI_TXFLTR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int dw_readl (struct dw_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_writel (struct dw_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_reset_chip (struct dw_spi*) ; 

__attribute__((used)) static void spi_hw_init(struct device *dev, struct dw_spi *dws)
{
	spi_reset_chip(dws);

	/*
	 * Try to detect the FIFO depth if not set by interface driver,
	 * the depth could be from 2 to 256 from HW spec
	 */
	if (!dws->fifo_len) {
		u32 fifo;

		for (fifo = 1; fifo < 256; fifo++) {
			dw_writel(dws, DW_SPI_TXFLTR, fifo);
			if (fifo != dw_readl(dws, DW_SPI_TXFLTR))
				break;
		}
		dw_writel(dws, DW_SPI_TXFLTR, 0);

		dws->fifo_len = (fifo == 1) ? 0 : fifo;
		dev_dbg(dev, "Detected FIFO size: %u bytes\n", dws->fifo_len);
	}

	/* enable HW fixup for explicit CS deselect for Amazon's alpine chip */
	if (dws->cs_override)
		dw_writel(dws, DW_SPI_CS_OVERRIDE, 0xF);
}