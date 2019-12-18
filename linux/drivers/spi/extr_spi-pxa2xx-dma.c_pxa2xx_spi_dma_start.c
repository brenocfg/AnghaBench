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
struct driver_data {int /*<<< orphan*/  dma_running; TYPE_1__* controller; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_tx; int /*<<< orphan*/  dma_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 

void pxa2xx_spi_dma_start(struct driver_data *drv_data)
{
	dma_async_issue_pending(drv_data->controller->dma_rx);
	dma_async_issue_pending(drv_data->controller->dma_tx);

	atomic_set(&drv_data->dma_running, 1);
}