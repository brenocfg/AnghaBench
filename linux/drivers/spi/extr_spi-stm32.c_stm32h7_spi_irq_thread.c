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
struct stm32_spi {scalar_t__ rx_len; scalar_t__ tx_len; int /*<<< orphan*/  lock; scalar_t__ base; scalar_t__ rx_buf; scalar_t__ cur_usedma; scalar_t__ tx_buf; int /*<<< orphan*/  dev; } ;
struct spi_master {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ STM32H7_SPI_IER ; 
 scalar_t__ STM32H7_SPI_IFCR ; 
 scalar_t__ STM32H7_SPI_SR ; 
 int STM32H7_SPI_SR_EOT ; 
 int STM32H7_SPI_SR_MODF ; 
 int STM32H7_SPI_SR_OVR ; 
 int STM32H7_SPI_SR_RXP ; 
 int STM32H7_SPI_SR_SUSP ; 
 int STM32H7_SPI_SR_TXP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct stm32_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32h7_spi_disable (struct stm32_spi*) ; 
 int /*<<< orphan*/  stm32h7_spi_read_rxfifo (struct stm32_spi*,int) ; 
 int /*<<< orphan*/  stm32h7_spi_write_txfifo (struct stm32_spi*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t stm32h7_spi_irq_thread(int irq, void *dev_id)
{
	struct spi_master *master = dev_id;
	struct stm32_spi *spi = spi_master_get_devdata(master);
	u32 sr, ier, mask;
	unsigned long flags;
	bool end = false;

	spin_lock_irqsave(&spi->lock, flags);

	sr = readl_relaxed(spi->base + STM32H7_SPI_SR);
	ier = readl_relaxed(spi->base + STM32H7_SPI_IER);

	mask = ier;
	/* EOTIE is triggered on EOT, SUSP and TXC events. */
	mask |= STM32H7_SPI_SR_SUSP;
	/*
	 * When TXTF is set, DXPIE and TXPIE are cleared. So in case of
	 * Full-Duplex, need to poll RXP event to know if there are remaining
	 * data, before disabling SPI.
	 */
	if (spi->rx_buf && !spi->cur_usedma)
		mask |= STM32H7_SPI_SR_RXP;

	if (!(sr & mask)) {
		dev_dbg(spi->dev, "spurious IT (sr=0x%08x, ier=0x%08x)\n",
			sr, ier);
		spin_unlock_irqrestore(&spi->lock, flags);
		return IRQ_NONE;
	}

	if (sr & STM32H7_SPI_SR_SUSP) {
		dev_warn(spi->dev, "Communication suspended\n");
		if (!spi->cur_usedma && (spi->rx_buf && (spi->rx_len > 0)))
			stm32h7_spi_read_rxfifo(spi, false);
		/*
		 * If communication is suspended while using DMA, it means
		 * that something went wrong, so stop the current transfer
		 */
		if (spi->cur_usedma)
			end = true;
	}

	if (sr & STM32H7_SPI_SR_MODF) {
		dev_warn(spi->dev, "Mode fault: transfer aborted\n");
		end = true;
	}

	if (sr & STM32H7_SPI_SR_OVR) {
		dev_warn(spi->dev, "Overrun: received value discarded\n");
		if (!spi->cur_usedma && (spi->rx_buf && (spi->rx_len > 0)))
			stm32h7_spi_read_rxfifo(spi, false);
		/*
		 * If overrun is detected while using DMA, it means that
		 * something went wrong, so stop the current transfer
		 */
		if (spi->cur_usedma)
			end = true;
	}

	if (sr & STM32H7_SPI_SR_EOT) {
		if (!spi->cur_usedma && (spi->rx_buf && (spi->rx_len > 0)))
			stm32h7_spi_read_rxfifo(spi, true);
		end = true;
	}

	if (sr & STM32H7_SPI_SR_TXP)
		if (!spi->cur_usedma && (spi->tx_buf && (spi->tx_len > 0)))
			stm32h7_spi_write_txfifo(spi);

	if (sr & STM32H7_SPI_SR_RXP)
		if (!spi->cur_usedma && (spi->rx_buf && (spi->rx_len > 0)))
			stm32h7_spi_read_rxfifo(spi, false);

	writel_relaxed(mask, spi->base + STM32H7_SPI_IFCR);

	spin_unlock_irqrestore(&spi->lock, flags);

	if (end) {
		spi_finalize_current_transfer(master);
		stm32h7_spi_disable(spi);
	}

	return IRQ_HANDLED;
}