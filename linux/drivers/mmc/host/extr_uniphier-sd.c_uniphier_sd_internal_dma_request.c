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
struct uniphier_sd_priv {int caps; } ;
struct tmio_mmc_host {int /*<<< orphan*/  dma_issue; void* chan_tx; void* chan_rx; } ;
struct tmio_mmc_data {int dummy; } ;

/* Variables and functions */
 int UNIPHIER_SD_CAP_BROKEN_DMA_RX ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  uniphier_sd_internal_dma_issue ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 

__attribute__((used)) static void uniphier_sd_internal_dma_request(struct tmio_mmc_host *host,
					     struct tmio_mmc_data *pdata)
{
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);

	/*
	 * Due to a hardware bug, Pro5 cannot use DMA for RX.
	 * We can still use DMA for TX, but PIO for RX.
	 */
	if (!(priv->caps & UNIPHIER_SD_CAP_BROKEN_DMA_RX))
		host->chan_rx = (void *)0xdeadbeaf;

	host->chan_tx = (void *)0xdeadbeaf;

	tasklet_init(&host->dma_issue, uniphier_sd_internal_dma_issue,
		     (unsigned long)host);
}