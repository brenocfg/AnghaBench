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
struct efm32_spi_ddata {scalar_t__ rx_len; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  REG_IEN ; 
 int REG_IF_RXDATAV ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int REG_STATUS_RXDATAV ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int efm32_spi_read32 (struct efm32_spi_ddata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_spi_rx_u8 (struct efm32_spi_ddata*) ; 
 int /*<<< orphan*/  efm32_spi_write32 (struct efm32_spi_ddata*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t efm32_spi_rxirq(int irq, void *data)
{
	struct efm32_spi_ddata *ddata = data;
	irqreturn_t ret = IRQ_NONE;

	spin_lock(&ddata->lock);

	while (ddata->rx_len > 0 &&
			efm32_spi_read32(ddata, REG_STATUS) &
			REG_STATUS_RXDATAV) {
		efm32_spi_rx_u8(ddata);

		ret = IRQ_HANDLED;
	}

	if (!ddata->rx_len) {
		u32 ien = efm32_spi_read32(ddata, REG_IEN);

		ien &= ~REG_IF_RXDATAV;

		efm32_spi_write32(ddata, ien, REG_IEN);

		complete(&ddata->done);
	}

	spin_unlock(&ddata->lock);

	return ret;
}