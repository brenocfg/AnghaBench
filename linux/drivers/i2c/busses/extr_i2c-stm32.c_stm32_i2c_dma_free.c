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
struct stm32_i2c_dma {int /*<<< orphan*/ * chan_using; int /*<<< orphan*/ * chan_rx; int /*<<< orphan*/ * chan_tx; scalar_t__ dma_len; scalar_t__ dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 

void stm32_i2c_dma_free(struct stm32_i2c_dma *dma)
{
	dma->dma_buf = 0;
	dma->dma_len = 0;

	dma_release_channel(dma->chan_tx);
	dma->chan_tx = NULL;

	dma_release_channel(dma->chan_rx);
	dma->chan_rx = NULL;

	dma->chan_using = NULL;
}