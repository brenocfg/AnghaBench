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
struct jz4740_mmc_host {int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  dma_tx; int /*<<< orphan*/  use_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jz4740_mmc_release_dma_channels(struct jz4740_mmc_host *host)
{
	if (!host->use_dma)
		return;

	dma_release_channel(host->dma_tx);
	dma_release_channel(host->dma_rx);
}