#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tmio_mmc_host {int dma_on; int /*<<< orphan*/  sg_len; TYPE_1__* pdev; struct scatterlist* sg_ptr; } ;
struct scatterlist {int dummy; } ;
struct mmc_data {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CM_DTRAN_MODE ; 
 int /*<<< orphan*/  DM_DTRAN_ADDR ; 
 int /*<<< orphan*/  DTRAN_MODE_ADDR_MODE ; 
 int /*<<< orphan*/  DTRAN_MODE_BUS_WIDTH ; 
 int /*<<< orphan*/  DTRAN_MODE_CH_NUM_CH0 ; 
 int /*<<< orphan*/  DTRAN_MODE_CH_NUM_CH1 ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  SDHI_INTERNAL_DMAC_ADDR_MODE_FIXED_ONLY ; 
 int /*<<< orphan*/  SDHI_INTERNAL_DMAC_ONE_RX_ONLY ; 
 int /*<<< orphan*/  SDHI_INTERNAL_DMAC_RX_IN_USE ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ *,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_flags ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 
 int /*<<< orphan*/  renesas_sdhi_internal_dmac_dm_write (struct tmio_mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  renesas_sdhi_internal_dmac_enable_dma (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
renesas_sdhi_internal_dmac_start_dma(struct tmio_mmc_host *host,
				     struct mmc_data *data)
{
	struct scatterlist *sg = host->sg_ptr;
	u32 dtran_mode = DTRAN_MODE_BUS_WIDTH;

	if (!test_bit(SDHI_INTERNAL_DMAC_ADDR_MODE_FIXED_ONLY, &global_flags))
		dtran_mode |= DTRAN_MODE_ADDR_MODE;

	if (!dma_map_sg(&host->pdev->dev, sg, host->sg_len,
			mmc_get_dma_dir(data)))
		goto force_pio;

	/* This DMAC cannot handle if buffer is not 8-bytes alignment */
	if (!IS_ALIGNED(sg_dma_address(sg), 8))
		goto force_pio_with_unmap;

	if (data->flags & MMC_DATA_READ) {
		dtran_mode |= DTRAN_MODE_CH_NUM_CH1;
		if (test_bit(SDHI_INTERNAL_DMAC_ONE_RX_ONLY, &global_flags) &&
		    test_and_set_bit(SDHI_INTERNAL_DMAC_RX_IN_USE, &global_flags))
			goto force_pio_with_unmap;
	} else {
		dtran_mode |= DTRAN_MODE_CH_NUM_CH0;
	}

	renesas_sdhi_internal_dmac_enable_dma(host, true);

	/* set dma parameters */
	renesas_sdhi_internal_dmac_dm_write(host, DM_CM_DTRAN_MODE,
					    dtran_mode);
	renesas_sdhi_internal_dmac_dm_write(host, DM_DTRAN_ADDR,
					    sg_dma_address(sg));

	host->dma_on = true;

	return;

force_pio_with_unmap:
	dma_unmap_sg(&host->pdev->dev, sg, host->sg_len, mmc_get_dma_dir(data));

force_pio:
	renesas_sdhi_internal_dmac_enable_dma(host, false);
}