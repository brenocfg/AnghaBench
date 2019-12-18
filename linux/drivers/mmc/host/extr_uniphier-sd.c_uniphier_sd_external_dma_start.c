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
struct uniphier_sd_priv {int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  chan; } ;
struct tmio_mmc_host {int dma_on; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg_ptr; int /*<<< orphan*/  mmc; } ;
struct mmc_data {int flags; } ;
struct dma_async_tx_descriptor {struct tmio_mmc_host* callback_param; int /*<<< orphan*/  callback_result; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  scalar_t__ dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int MMC_DATA_READ ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_sd_dma_endisable (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_sd_external_dma_callback ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 

__attribute__((used)) static void uniphier_sd_external_dma_start(struct tmio_mmc_host *host,
					   struct mmc_data *data)
{
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);
	enum dma_transfer_direction dma_tx_dir;
	struct dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	int sg_len;

	if (!priv->chan)
		goto force_pio;

	if (data->flags & MMC_DATA_READ) {
		priv->dma_dir = DMA_FROM_DEVICE;
		dma_tx_dir = DMA_DEV_TO_MEM;
	} else {
		priv->dma_dir = DMA_TO_DEVICE;
		dma_tx_dir = DMA_MEM_TO_DEV;
	}

	sg_len = dma_map_sg(mmc_dev(host->mmc), host->sg_ptr, host->sg_len,
			    priv->dma_dir);
	if (sg_len == 0)
		goto force_pio;

	desc = dmaengine_prep_slave_sg(priv->chan, host->sg_ptr, sg_len,
				       dma_tx_dir, DMA_CTRL_ACK);
	if (!desc)
		goto unmap_sg;

	desc->callback_result = uniphier_sd_external_dma_callback;
	desc->callback_param = host;

	cookie = dmaengine_submit(desc);
	if (cookie < 0)
		goto unmap_sg;

	host->dma_on = true;

	return;

unmap_sg:
	dma_unmap_sg(mmc_dev(host->mmc), host->sg_ptr, host->sg_len,
		     priv->dma_dir);
force_pio:
	uniphier_sd_dma_endisable(host, 0);
}