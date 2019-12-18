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
struct omap_hsmmc_host {int req_in_progress; int dma_ch; int flags; struct mmc_request* mrq; int /*<<< orphan*/  fclk; int /*<<< orphan*/  clk_rate; scalar_t__ reqs_blocked; } ;
struct mmc_request {TYPE_2__* data; TYPE_1__* cmd; TYPE_1__* sbc; } ;
struct mmc_host {int dummy; } ;
struct TYPE_4__ {int error; } ;
struct TYPE_3__ {int error; } ;

/* Variables and functions */
 int AUTO_CMD23 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 struct omap_hsmmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int omap_hsmmc_prepare_data (struct omap_hsmmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  omap_hsmmc_start_command (struct omap_hsmmc_host*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  omap_hsmmc_start_dma_transfer (struct omap_hsmmc_host*) ; 

__attribute__((used)) static void omap_hsmmc_request(struct mmc_host *mmc, struct mmc_request *req)
{
	struct omap_hsmmc_host *host = mmc_priv(mmc);
	int err;

	BUG_ON(host->req_in_progress);
	BUG_ON(host->dma_ch != -1);
	if (host->reqs_blocked)
		host->reqs_blocked = 0;
	WARN_ON(host->mrq != NULL);
	host->mrq = req;
	host->clk_rate = clk_get_rate(host->fclk);
	err = omap_hsmmc_prepare_data(host, req);
	if (err) {
		req->cmd->error = err;
		if (req->data)
			req->data->error = err;
		host->mrq = NULL;
		mmc_request_done(mmc, req);
		return;
	}
	if (req->sbc && !(host->flags & AUTO_CMD23)) {
		omap_hsmmc_start_command(host, req->sbc, NULL);
		return;
	}

	omap_hsmmc_start_dma_transfer(host);
	omap_hsmmc_start_command(host, req->cmd, req->data);
}