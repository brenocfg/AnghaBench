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
struct tmio_mmc_host {int /*<<< orphan*/ * chan_tx; int /*<<< orphan*/  chan_rx; } ;

/* Variables and functions */

__attribute__((used)) static void
renesas_sdhi_internal_dmac_release_dma(struct tmio_mmc_host *host)
{
	/* Each value is set to zero to assume "disabling" each DMA */
	host->chan_rx = host->chan_tx = NULL;
}