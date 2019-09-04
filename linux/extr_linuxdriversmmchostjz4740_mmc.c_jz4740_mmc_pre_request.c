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
struct mmc_request {struct mmc_data* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {scalar_t__ host_cookie; } ;
struct jz4740_mmc_host_next {int dummy; } ;
struct jz4740_mmc_host {scalar_t__ use_dma; struct jz4740_mmc_host_next next_data; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 struct dma_chan* jz4740_mmc_get_dma_chan (struct jz4740_mmc_host*,struct mmc_data*) ; 
 scalar_t__ jz4740_mmc_prepare_dma_data (struct jz4740_mmc_host*,struct mmc_data*,struct jz4740_mmc_host_next*,struct dma_chan*) ; 
 struct jz4740_mmc_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void jz4740_mmc_pre_request(struct mmc_host *mmc,
				   struct mmc_request *mrq)
{
	struct jz4740_mmc_host *host = mmc_priv(mmc);
	struct mmc_data *data = mrq->data;
	struct jz4740_mmc_host_next *next_data = &host->next_data;

	BUG_ON(data->host_cookie);

	if (host->use_dma) {
		struct dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);

		if (jz4740_mmc_prepare_dma_data(host, data, next_data, chan))
			data->host_cookie = 0;
	}
}