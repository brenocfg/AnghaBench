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
struct spi_controller {int /*<<< orphan*/ * dma_tx; void* dma_rx; } ;
struct pxa2xx_spi_controller {int /*<<< orphan*/  rx_param; int /*<<< orphan*/  dma_filter; int /*<<< orphan*/  tx_param; } ;
struct driver_data {struct spi_controller* controller; TYPE_1__* pdev; struct pxa2xx_spi_controller* controller_info; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 int ENODEV ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 void* dma_request_slave_channel_compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*,char*) ; 

int pxa2xx_spi_dma_setup(struct driver_data *drv_data)
{
	struct pxa2xx_spi_controller *pdata = drv_data->controller_info;
	struct device *dev = &drv_data->pdev->dev;
	struct spi_controller *controller = drv_data->controller;
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	controller->dma_tx = dma_request_slave_channel_compat(mask,
				pdata->dma_filter, pdata->tx_param, dev, "tx");
	if (!controller->dma_tx)
		return -ENODEV;

	controller->dma_rx = dma_request_slave_channel_compat(mask,
				pdata->dma_filter, pdata->rx_param, dev, "rx");
	if (!controller->dma_rx) {
		dma_release_channel(controller->dma_tx);
		controller->dma_tx = NULL;
		return -ENODEV;
	}

	return 0;
}