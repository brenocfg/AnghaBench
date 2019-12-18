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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_sd_priv {int /*<<< orphan*/  dma_dir; } ;
struct tmio_mmc_host {int sg_len; int dma_on; scalar_t__ ctl; int /*<<< orphan*/  mmc; int /*<<< orphan*/  chan_rx; struct scatterlist* sg_ptr; } ;
struct scatterlist {int /*<<< orphan*/  offset; } ;
struct mmc_data {int flags; int /*<<< orphan*/  sg; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int MMC_DATA_READ ; 
 scalar_t__ UNIPHIER_SD_DMA_ADDR_H ; 
 scalar_t__ UNIPHIER_SD_DMA_ADDR_L ; 
 scalar_t__ UNIPHIER_SD_DMA_MODE ; 
 int /*<<< orphan*/  UNIPHIER_SD_DMA_MODE_ADDR_INC ; 
 unsigned int UNIPHIER_SD_DMA_MODE_DIR_FROM_DEV ; 
 int /*<<< orphan*/  UNIPHIER_SD_DMA_MODE_DIR_MASK ; 
 unsigned int UNIPHIER_SD_DMA_MODE_DIR_TO_DEV ; 
 unsigned int UNIPHIER_SD_DMA_MODE_WIDTH_64 ; 
 int /*<<< orphan*/  UNIPHIER_SD_DMA_MODE_WIDTH_MASK ; 
 scalar_t__ WARN_ON (int) ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_sd_dma_endisable (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uniphier_sd_internal_dma_start(struct tmio_mmc_host *host,
					   struct mmc_data *data)
{
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);
	struct scatterlist *sg = host->sg_ptr;
	dma_addr_t dma_addr;
	unsigned int dma_mode_dir;
	u32 dma_mode;
	int sg_len;

	if ((data->flags & MMC_DATA_READ) && !host->chan_rx)
		goto force_pio;

	if (WARN_ON(host->sg_len != 1))
		goto force_pio;

	if (!IS_ALIGNED(sg->offset, 8))
		goto force_pio;

	if (data->flags & MMC_DATA_READ) {
		priv->dma_dir = DMA_FROM_DEVICE;
		dma_mode_dir = UNIPHIER_SD_DMA_MODE_DIR_FROM_DEV;
	} else {
		priv->dma_dir = DMA_TO_DEVICE;
		dma_mode_dir = UNIPHIER_SD_DMA_MODE_DIR_TO_DEV;
	}

	sg_len = dma_map_sg(mmc_dev(host->mmc), sg, 1, priv->dma_dir);
	if (sg_len == 0)
		goto force_pio;

	dma_mode = FIELD_PREP(UNIPHIER_SD_DMA_MODE_DIR_MASK, dma_mode_dir);
	dma_mode |= FIELD_PREP(UNIPHIER_SD_DMA_MODE_WIDTH_MASK,
			       UNIPHIER_SD_DMA_MODE_WIDTH_64);
	dma_mode |= UNIPHIER_SD_DMA_MODE_ADDR_INC;

	writel(dma_mode, host->ctl + UNIPHIER_SD_DMA_MODE);

	dma_addr = sg_dma_address(data->sg);
	writel(lower_32_bits(dma_addr), host->ctl + UNIPHIER_SD_DMA_ADDR_L);
	writel(upper_32_bits(dma_addr), host->ctl + UNIPHIER_SD_DMA_ADDR_H);

	host->dma_on = true;

	return;
force_pio:
	uniphier_sd_dma_endisable(host, 0);
}