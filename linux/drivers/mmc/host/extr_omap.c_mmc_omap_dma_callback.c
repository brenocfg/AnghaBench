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
struct mmc_omap_host {struct mmc_data* data; } ;
struct mmc_data {int bytes_xfered; int blocks; int blksz; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_omap_dma_done (struct mmc_omap_host*,struct mmc_data*) ; 

__attribute__((used)) static void mmc_omap_dma_callback(void *priv)
{
	struct mmc_omap_host *host = priv;
	struct mmc_data *data = host->data;

	/* If we got to the end of DMA, assume everything went well */
	data->bytes_xfered += data->blocks * data->blksz;

	mmc_omap_dma_done(host, data);
}