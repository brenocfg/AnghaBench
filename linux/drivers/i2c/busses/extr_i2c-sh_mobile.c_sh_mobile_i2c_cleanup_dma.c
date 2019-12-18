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
struct sh_mobile_i2c_data {scalar_t__ dma_direction; int /*<<< orphan*/  dma_tx; int /*<<< orphan*/  dma_rx; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_NONE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mobile_i2c_dma_unmap (struct sh_mobile_i2c_data*) ; 

__attribute__((used)) static void sh_mobile_i2c_cleanup_dma(struct sh_mobile_i2c_data *pd)
{
	if (pd->dma_direction == DMA_NONE)
		return;
	else if (pd->dma_direction == DMA_FROM_DEVICE)
		dmaengine_terminate_all(pd->dma_rx);
	else if (pd->dma_direction == DMA_TO_DEVICE)
		dmaengine_terminate_all(pd->dma_tx);

	sh_mobile_i2c_dma_unmap(pd);
}