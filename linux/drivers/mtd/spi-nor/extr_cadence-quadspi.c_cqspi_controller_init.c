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
struct cqspi_st {int fifo_depth; int trigger_address; int fifo_width; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ CQSPI_REG_CONFIG ; 
 int CQSPI_REG_CONFIG_ENB_DIR_ACC_CTRL ; 
 scalar_t__ CQSPI_REG_INDIRECTRDWATERMARK ; 
 scalar_t__ CQSPI_REG_INDIRECTTRIGGER ; 
 scalar_t__ CQSPI_REG_INDIRECTWRWATERMARK ; 
 scalar_t__ CQSPI_REG_IRQMASK ; 
 scalar_t__ CQSPI_REG_REMAP ; 
 scalar_t__ CQSPI_REG_SRAMPARTITION ; 
 int /*<<< orphan*/  cqspi_controller_enable (struct cqspi_st*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cqspi_controller_init(struct cqspi_st *cqspi)
{
	u32 reg;

	cqspi_controller_enable(cqspi, 0);

	/* Configure the remap address register, no remap */
	writel(0, cqspi->iobase + CQSPI_REG_REMAP);

	/* Disable all interrupts. */
	writel(0, cqspi->iobase + CQSPI_REG_IRQMASK);

	/* Configure the SRAM split to 1:1 . */
	writel(cqspi->fifo_depth / 2, cqspi->iobase + CQSPI_REG_SRAMPARTITION);

	/* Load indirect trigger address. */
	writel(cqspi->trigger_address,
	       cqspi->iobase + CQSPI_REG_INDIRECTTRIGGER);

	/* Program read watermark -- 1/2 of the FIFO. */
	writel(cqspi->fifo_depth * cqspi->fifo_width / 2,
	       cqspi->iobase + CQSPI_REG_INDIRECTRDWATERMARK);
	/* Program write watermark -- 1/8 of the FIFO. */
	writel(cqspi->fifo_depth * cqspi->fifo_width / 8,
	       cqspi->iobase + CQSPI_REG_INDIRECTWRWATERMARK);

	/* Enable Direct Access Controller */
	reg = readl(cqspi->iobase + CQSPI_REG_CONFIG);
	reg |= CQSPI_REG_CONFIG_ENB_DIR_ACC_CTRL;
	writel(reg, cqspi->iobase + CQSPI_REG_CONFIG);

	cqspi_controller_enable(cqspi, 1);
}