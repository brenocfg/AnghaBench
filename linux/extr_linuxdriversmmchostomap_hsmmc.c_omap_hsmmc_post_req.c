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
struct omap_hsmmc_host {scalar_t__ use_dma; } ;
struct mmc_request {struct mmc_data* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {scalar_t__ host_cookie; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 
 struct omap_hsmmc_host* mmc_priv (struct mmc_host*) ; 
 struct dma_chan* omap_hsmmc_get_dma_chan (struct omap_hsmmc_host*,struct mmc_data*) ; 

__attribute__((used)) static void omap_hsmmc_post_req(struct mmc_host *mmc, struct mmc_request *mrq,
				int err)
{
	struct omap_hsmmc_host *host = mmc_priv(mmc);
	struct mmc_data *data = mrq->data;

	if (host->use_dma && data->host_cookie) {
		struct dma_chan *c = omap_hsmmc_get_dma_chan(host, data);

		dma_unmap_sg(c->device->dev, data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
		data->host_cookie = 0;
	}
}