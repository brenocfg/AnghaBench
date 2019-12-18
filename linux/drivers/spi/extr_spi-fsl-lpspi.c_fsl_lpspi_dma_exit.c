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
struct spi_controller {int /*<<< orphan*/ * dma_tx; int /*<<< orphan*/ * dma_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_lpspi_dma_exit(struct spi_controller *controller)
{
	if (controller->dma_rx) {
		dma_release_channel(controller->dma_rx);
		controller->dma_rx = NULL;
	}

	if (controller->dma_tx) {
		dma_release_channel(controller->dma_tx);
		controller->dma_tx = NULL;
	}
}