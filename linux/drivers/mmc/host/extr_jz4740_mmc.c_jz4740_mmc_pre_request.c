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
struct mmc_data {void* host_cookie; } ;
struct jz4740_mmc_host {int /*<<< orphan*/  use_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  COOKIE_PREMAPPED ; 
 void* COOKIE_UNMAPPED ; 
 scalar_t__ jz4740_mmc_prepare_dma_data (struct jz4740_mmc_host*,struct mmc_data*,int /*<<< orphan*/ ) ; 
 struct jz4740_mmc_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void jz4740_mmc_pre_request(struct mmc_host *mmc,
				   struct mmc_request *mrq)
{
	struct jz4740_mmc_host *host = mmc_priv(mmc);
	struct mmc_data *data = mrq->data;

	if (!host->use_dma)
		return;

	data->host_cookie = COOKIE_UNMAPPED;
	if (jz4740_mmc_prepare_dma_data(host, data, COOKIE_PREMAPPED) < 0)
		data->host_cookie = COOKIE_UNMAPPED;
}