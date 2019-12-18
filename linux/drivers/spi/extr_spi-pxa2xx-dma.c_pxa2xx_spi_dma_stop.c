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
struct driver_data {TYPE_1__* controller; int /*<<< orphan*/  dma_running; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_tx; int /*<<< orphan*/  dma_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ ) ; 

void pxa2xx_spi_dma_stop(struct driver_data *drv_data)
{
	atomic_set(&drv_data->dma_running, 0);
	dmaengine_terminate_sync(drv_data->controller->dma_rx);
	dmaengine_terminate_sync(drv_data->controller->dma_tx);
}