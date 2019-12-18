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
struct sirfsoc_spi {int type; TYPE_1__* regs; scalar_t__ base; int /*<<< orphan*/  rx_done; int /*<<< orphan*/  tx_done; scalar_t__ tx_by_cmd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ int_st; scalar_t__ usp_int_en_clr; scalar_t__ int_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SIRFSOC_SPI_FRM_END ; 
 unsigned long SIRFSOC_SPI_RX_IO_DMA ; 
 int SIRFSOC_SPI_RX_OFLOW ; 
 int SIRFSOC_SPI_TXFIFO_EMPTY ; 
 int SIRFSOC_SPI_TX_UFLOW ; 
#define  SIRF_REAL_SPI 130 
#define  SIRF_USP_SPI_A7 129 
#define  SIRF_USP_SPI_P2 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static irqreturn_t spi_sirfsoc_irq(int irq, void *dev_id)
{
	struct sirfsoc_spi *sspi = dev_id;
	u32 spi_stat;

	spi_stat = readl(sspi->base + sspi->regs->int_st);
	if (sspi->tx_by_cmd && sspi->type == SIRF_REAL_SPI
		&& (spi_stat & SIRFSOC_SPI_FRM_END)) {
		complete(&sspi->tx_done);
		writel(0x0, sspi->base + sspi->regs->int_en);
		writel(readl(sspi->base + sspi->regs->int_st),
				sspi->base + sspi->regs->int_st);
		return IRQ_HANDLED;
	}
	/* Error Conditions */
	if (spi_stat & SIRFSOC_SPI_RX_OFLOW ||
			spi_stat & SIRFSOC_SPI_TX_UFLOW) {
		complete(&sspi->tx_done);
		complete(&sspi->rx_done);
		switch (sspi->type) {
		case SIRF_REAL_SPI:
		case SIRF_USP_SPI_P2:
			writel(0x0, sspi->base + sspi->regs->int_en);
			break;
		case SIRF_USP_SPI_A7:
			writel(~0UL, sspi->base + sspi->regs->usp_int_en_clr);
			break;
		}
		writel(readl(sspi->base + sspi->regs->int_st),
				sspi->base + sspi->regs->int_st);
		return IRQ_HANDLED;
	}
	if (spi_stat & SIRFSOC_SPI_TXFIFO_EMPTY)
		complete(&sspi->tx_done);
	while (!(readl(sspi->base + sspi->regs->int_st) &
		SIRFSOC_SPI_RX_IO_DMA))
		cpu_relax();
	complete(&sspi->rx_done);
	switch (sspi->type) {
	case SIRF_REAL_SPI:
	case SIRF_USP_SPI_P2:
		writel(0x0, sspi->base + sspi->regs->int_en);
		break;
	case SIRF_USP_SPI_A7:
		writel(~0UL, sspi->base + sspi->regs->usp_int_en_clr);
		break;
	}
	writel(readl(sspi->base + sspi->regs->int_st),
			sspi->base + sspi->regs->int_st);

	return IRQ_HANDLED;
}