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
struct tmio_mmc_host {scalar_t__ chan_tx; scalar_t__ chan_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_terminate_all (scalar_t__) ; 
 int /*<<< orphan*/  renesas_sdhi_sys_dmac_enable_dma (struct tmio_mmc_host*,int) ; 

__attribute__((used)) static void renesas_sdhi_sys_dmac_abort_dma(struct tmio_mmc_host *host)
{
	renesas_sdhi_sys_dmac_enable_dma(host, false);

	if (host->chan_rx)
		dmaengine_terminate_all(host->chan_rx);
	if (host->chan_tx)
		dmaengine_terminate_all(host->chan_tx);

	renesas_sdhi_sys_dmac_enable_dma(host, true);
}