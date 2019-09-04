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
struct stm32_qspi {scalar_t__ io_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_completion; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CR_TCIE ; 
 int FCR_CTCF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ QUADSPI_CR ; 
 scalar_t__ QUADSPI_FCR ; 
 scalar_t__ QUADSPI_SR ; 
 int SR_TCF ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t stm32_qspi_irq(int irq, void *dev_id)
{
	struct stm32_qspi *qspi = (struct stm32_qspi *)dev_id;
	u32 cr, sr, fcr = 0;

	cr = readl_relaxed(qspi->io_base + QUADSPI_CR);
	sr = readl_relaxed(qspi->io_base + QUADSPI_SR);

	if ((cr & CR_TCIE) && (sr & SR_TCF)) {
		/* tx complete */
		fcr |= FCR_CTCF;
		complete(&qspi->cmd_completion);
	} else {
		dev_info_ratelimited(qspi->dev, "spurious interrupt\n");
	}

	writel_relaxed(fcr, qspi->io_base + QUADSPI_FCR);

	return IRQ_HANDLED;
}