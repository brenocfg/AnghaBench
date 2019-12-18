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
struct stm32_spi {int cur_usedma; TYPE_1__* cfg; int /*<<< orphan*/  dev; scalar_t__ rx_buf; int /*<<< orphan*/  rx_len; scalar_t__ tx_buf; int /*<<< orphan*/  tx_len; } ;
struct spi_transfer {int /*<<< orphan*/  len; scalar_t__ rx_buf; scalar_t__ tx_buf; } ;
struct spi_master {scalar_t__ (* can_dma ) (struct spi_master*,struct spi_device*,struct spi_transfer*) ;} ;
struct spi_device {int dummy; } ;
struct TYPE_2__ {int (* transfer_one_irq ) (struct stm32_spi*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct stm32_spi* spi_master_get_devdata (struct spi_master*) ; 
 int stm32_spi_transfer_one_dma (struct stm32_spi*,struct spi_transfer*) ; 
 int stm32_spi_transfer_one_setup (struct stm32_spi*,struct spi_device*,struct spi_transfer*) ; 
 scalar_t__ stub1 (struct spi_master*,struct spi_device*,struct spi_transfer*) ; 
 int stub2 (struct stm32_spi*) ; 

__attribute__((used)) static int stm32_spi_transfer_one(struct spi_master *master,
				  struct spi_device *spi_dev,
				  struct spi_transfer *transfer)
{
	struct stm32_spi *spi = spi_master_get_devdata(master);
	int ret;

	spi->tx_buf = transfer->tx_buf;
	spi->rx_buf = transfer->rx_buf;
	spi->tx_len = spi->tx_buf ? transfer->len : 0;
	spi->rx_len = spi->rx_buf ? transfer->len : 0;

	spi->cur_usedma = (master->can_dma &&
			   master->can_dma(master, spi_dev, transfer));

	ret = stm32_spi_transfer_one_setup(spi, spi_dev, transfer);
	if (ret) {
		dev_err(spi->dev, "SPI transfer setup failed\n");
		return ret;
	}

	if (spi->cur_usedma)
		return stm32_spi_transfer_one_dma(spi, transfer);
	else
		return spi->cfg->transfer_one_irq(spi);
}