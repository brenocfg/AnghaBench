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
struct spi_master {int dummy; } ;
struct rockchip_spi {scalar_t__ regs; int /*<<< orphan*/  rx_left; scalar_t__ tx_left; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ ROCKCHIP_SPI_IMR ; 
 int /*<<< orphan*/  rockchip_spi_pio_reader (struct rockchip_spi*) ; 
 int /*<<< orphan*/  rockchip_spi_pio_writer (struct rockchip_spi*) ; 
 int /*<<< orphan*/  spi_enable_chip (struct rockchip_spi*,int) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct rockchip_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t rockchip_spi_isr(int irq, void *dev_id)
{
	struct spi_master *master = dev_id;
	struct rockchip_spi *rs = spi_master_get_devdata(master);

	if (rs->tx_left)
		rockchip_spi_pio_writer(rs);

	rockchip_spi_pio_reader(rs);
	if (!rs->rx_left) {
		spi_enable_chip(rs, false);
		writel_relaxed(0, rs->regs + ROCKCHIP_SPI_IMR);
		spi_finalize_current_transfer(master);
	}

	return IRQ_HANDLED;
}