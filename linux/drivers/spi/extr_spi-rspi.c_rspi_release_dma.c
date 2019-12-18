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
struct spi_controller {scalar_t__ dma_rx; scalar_t__ dma_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 

__attribute__((used)) static void rspi_release_dma(struct spi_controller *ctlr)
{
	if (ctlr->dma_tx)
		dma_release_channel(ctlr->dma_tx);
	if (ctlr->dma_rx)
		dma_release_channel(ctlr->dma_rx);
}