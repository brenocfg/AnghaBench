#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usdhi6_host {int dma_active; TYPE_4__* chan_tx; TYPE_2__* chan_rx; TYPE_5__* mrq; } ;
struct mmc_data {int flags; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct TYPE_10__ {struct mmc_data* data; } ;
struct TYPE_9__ {TYPE_3__* device; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_1__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  USDHI6_CC_EXT_MODE ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usdhi6_write (struct usdhi6_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usdhi6_dma_stop_unmap(struct usdhi6_host *host)
{
	struct mmc_data *data = host->mrq->data;

	if (!host->dma_active)
		return;

	usdhi6_write(host, USDHI6_CC_EXT_MODE, 0);
	host->dma_active = false;

	if (data->flags & MMC_DATA_READ)
		dma_unmap_sg(host->chan_rx->device->dev, data->sg,
			     data->sg_len, DMA_FROM_DEVICE);
	else
		dma_unmap_sg(host->chan_tx->device->dev, data->sg,
			     data->sg_len, DMA_TO_DEVICE);
}