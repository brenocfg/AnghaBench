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
struct mmc_omap_host {int /*<<< orphan*/  sg_len; struct dma_chan* dma_rx; struct dma_chan* dma_tx; int /*<<< orphan*/  mmc; } ;
struct mmc_data {int flags; int /*<<< orphan*/  sg; scalar_t__ bytes_xfered; scalar_t__ error; } ;
struct dma_chan {TYPE_1__* device; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (struct dma_chan*) ; 
 struct device* mmc_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmc_omap_release_dma(struct mmc_omap_host *host, struct mmc_data *data,
		     int abort)
{
	enum dma_data_direction dma_data_dir;
	struct device *dev = mmc_dev(host->mmc);
	struct dma_chan *c;

	if (data->flags & MMC_DATA_WRITE) {
		dma_data_dir = DMA_TO_DEVICE;
		c = host->dma_tx;
	} else {
		dma_data_dir = DMA_FROM_DEVICE;
		c = host->dma_rx;
	}
	if (c) {
		if (data->error) {
			dmaengine_terminate_all(c);
			/* Claim nothing transferred on error... */
			data->bytes_xfered = 0;
		}
		dev = c->device->dev;
	}
	dma_unmap_sg(dev, data->sg, host->sg_len, dma_data_dir);
}