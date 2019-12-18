#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tmio_mmc_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg_ptr; TYPE_1__* pdev; TYPE_2__* data; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  SDHI_INTERNAL_DMAC_RX_IN_USE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  global_flags ; 
 int /*<<< orphan*/  renesas_sdhi_internal_dmac_enable_dma (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmio_mmc_do_data_irq (struct tmio_mmc_host*) ; 

__attribute__((used)) static void renesas_sdhi_internal_dmac_complete_tasklet_fn(unsigned long arg)
{
	struct tmio_mmc_host *host = (struct tmio_mmc_host *)arg;
	enum dma_data_direction dir;

	spin_lock_irq(&host->lock);

	if (!host->data)
		goto out;

	if (host->data->flags & MMC_DATA_READ)
		dir = DMA_FROM_DEVICE;
	else
		dir = DMA_TO_DEVICE;

	renesas_sdhi_internal_dmac_enable_dma(host, false);
	dma_unmap_sg(&host->pdev->dev, host->sg_ptr, host->sg_len, dir);

	if (dir == DMA_FROM_DEVICE)
		clear_bit(SDHI_INTERNAL_DMAC_RX_IN_USE, &global_flags);

	tmio_mmc_do_data_irq(host);
out:
	spin_unlock_irq(&host->lock);
}