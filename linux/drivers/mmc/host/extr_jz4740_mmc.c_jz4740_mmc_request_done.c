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
struct mmc_data {scalar_t__ host_cookie; } ;
struct jz4740_mmc_host {int /*<<< orphan*/  mmc; struct mmc_request* req; } ;

/* Variables and functions */
 scalar_t__ COOKIE_MAPPED ; 
 int /*<<< orphan*/  jz4740_mmc_dma_unmap (struct jz4740_mmc_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 

__attribute__((used)) static void jz4740_mmc_request_done(struct jz4740_mmc_host *host)
{
	struct mmc_request *req;
	struct mmc_data *data;

	req = host->req;
	data = req->data;
	host->req = NULL;

	if (data && data->host_cookie == COOKIE_MAPPED)
		jz4740_mmc_dma_unmap(host, data);
	mmc_request_done(host->mmc, req);
}