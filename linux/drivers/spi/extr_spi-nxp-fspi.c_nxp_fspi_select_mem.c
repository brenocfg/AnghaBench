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
typedef  int /*<<< orphan*/  uint64_t ;
struct spi_device {unsigned long max_speed_hz; int chip_select; } ;
struct nxp_fspi {int selected; int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; scalar_t__ iobase; int /*<<< orphan*/  memmap_phy_size; } ;

/* Variables and functions */
 scalar_t__ FSPI_FLSHA1CR0 ; 
 scalar_t__ FSPI_FLSHA2CR0 ; 
 scalar_t__ FSPI_FLSHB1CR0 ; 
 scalar_t__ FSPI_FLSHB2CR0 ; 
 int /*<<< orphan*/  FSPI_FLSHXCR0_SZ (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fspi_writel (struct nxp_fspi*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nxp_fspi_clk_disable_unprep (struct nxp_fspi*) ; 
 int nxp_fspi_clk_prep_enable (struct nxp_fspi*) ; 

__attribute__((used)) static void nxp_fspi_select_mem(struct nxp_fspi *f, struct spi_device *spi)
{
	unsigned long rate = spi->max_speed_hz;
	int ret;
	uint64_t size_kb;

	/*
	 * Return, if previously selected slave device is same as current
	 * requested slave device.
	 */
	if (f->selected == spi->chip_select)
		return;

	/* Reset FLSHxxCR0 registers */
	fspi_writel(f, 0, f->iobase + FSPI_FLSHA1CR0);
	fspi_writel(f, 0, f->iobase + FSPI_FLSHA2CR0);
	fspi_writel(f, 0, f->iobase + FSPI_FLSHB1CR0);
	fspi_writel(f, 0, f->iobase + FSPI_FLSHB2CR0);

	/* Assign controller memory mapped space as size, KBytes, of flash. */
	size_kb = FSPI_FLSHXCR0_SZ(f->memmap_phy_size);

	fspi_writel(f, size_kb, f->iobase + FSPI_FLSHA1CR0 +
		    4 * spi->chip_select);

	dev_dbg(f->dev, "Slave device [CS:%x] selected\n", spi->chip_select);

	nxp_fspi_clk_disable_unprep(f);

	ret = clk_set_rate(f->clk, rate);
	if (ret)
		return;

	ret = nxp_fspi_clk_prep_enable(f);
	if (ret)
		return;

	f->selected = spi->chip_select;
}