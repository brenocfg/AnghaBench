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
struct mmc_request {struct mmc_command* cmd; struct mmc_command* sbc; TYPE_1__* data; } ;
struct mmc_host {int dummy; } ;
struct mmc_command {scalar_t__ error; } ;
struct meson_mx_mmc_host {scalar_t__ base; struct mmc_request* mrq; scalar_t__ error; } ;
struct TYPE_2__ {int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 scalar_t__ MESON_MX_SDIO_ADDR ; 
 scalar_t__ meson_mx_mmc_map_dma (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  meson_mx_mmc_start_cmd (struct mmc_host*,struct mmc_command*) ; 
 struct meson_mx_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_mx_mmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct meson_mx_mmc_host *host = mmc_priv(mmc);
	struct mmc_command *cmd = mrq->cmd;

	if (!host->error)
		host->error = meson_mx_mmc_map_dma(mmc, mrq);

	if (host->error) {
		cmd->error = host->error;
		mmc_request_done(mmc, mrq);
		return;
	}

	host->mrq = mrq;

	if (mrq->data)
		writel(sg_dma_address(mrq->data->sg),
		       host->base + MESON_MX_SDIO_ADDR);

	if (mrq->sbc)
		meson_mx_mmc_start_cmd(mmc, mrq->sbc);
	else
		meson_mx_mmc_start_cmd(mmc, mrq->cmd);
}