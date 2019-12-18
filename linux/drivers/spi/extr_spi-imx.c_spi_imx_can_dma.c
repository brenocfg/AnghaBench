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
struct spi_transfer {scalar_t__ len; } ;
struct spi_master {int /*<<< orphan*/  dma_rx; } ;
struct spi_imx_data {scalar_t__ dynamic_burst; TYPE_1__* devtype_data; scalar_t__ slave_mode; } ;
struct spi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ fifo_size; } ;

/* Variables and functions */
 struct spi_imx_data* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  use_dma ; 

__attribute__((used)) static bool spi_imx_can_dma(struct spi_master *master, struct spi_device *spi,
			 struct spi_transfer *transfer)
{
	struct spi_imx_data *spi_imx = spi_master_get_devdata(master);

	if (!use_dma)
		return false;

	if (!master->dma_rx)
		return false;

	if (spi_imx->slave_mode)
		return false;

	if (transfer->len < spi_imx->devtype_data->fifo_size)
		return false;

	spi_imx->dynamic_burst = 0;

	return true;
}