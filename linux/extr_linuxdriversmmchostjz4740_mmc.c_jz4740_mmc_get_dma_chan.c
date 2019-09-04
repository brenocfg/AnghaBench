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
struct mmc_data {int flags; } ;
struct jz4740_mmc_host {struct dma_chan* dma_tx; struct dma_chan* dma_rx; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 

__attribute__((used)) static inline struct dma_chan *jz4740_mmc_get_dma_chan(struct jz4740_mmc_host *host,
						       struct mmc_data *data)
{
	return (data->flags & MMC_DATA_READ) ? host->dma_rx : host->dma_tx;
}