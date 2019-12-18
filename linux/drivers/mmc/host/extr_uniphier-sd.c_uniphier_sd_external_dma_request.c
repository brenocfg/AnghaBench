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
struct uniphier_sd_priv {struct dma_chan* chan; } ;
struct tmio_mmc_host {int /*<<< orphan*/  dma_issue; struct dma_chan* chan_tx; struct dma_chan* chan_rx; int /*<<< orphan*/  mmc; } ;
struct tmio_mmc_data {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct dma_chan* dma_request_chan (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  uniphier_sd_external_dma_issue ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 

__attribute__((used)) static void uniphier_sd_external_dma_request(struct tmio_mmc_host *host,
					     struct tmio_mmc_data *pdata)
{
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);
	struct dma_chan *chan;

	chan = dma_request_chan(mmc_dev(host->mmc), "rx-tx");
	if (IS_ERR(chan)) {
		dev_warn(mmc_dev(host->mmc),
			 "failed to request DMA channel. falling back to PIO\n");
		return;	/* just use PIO even for -EPROBE_DEFER */
	}

	/* this driver uses a single channel for both RX an TX */
	priv->chan = chan;
	host->chan_rx = chan;
	host->chan_tx = chan;

	tasklet_init(&host->dma_issue, uniphier_sd_external_dma_issue,
		     (unsigned long)host);
}