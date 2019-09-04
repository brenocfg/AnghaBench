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
struct mmc_request {int /*<<< orphan*/  cmd; scalar_t__ sbc; TYPE_1__* data; } ;
struct mmc_host {int dummy; } ;
struct meson_host {scalar_t__ regs; } ;
struct TYPE_2__ {int host_cookie; } ;

/* Variables and functions */
 int SD_EMMC_PRE_REQ_DONE ; 
 scalar_t__ SD_EMMC_START ; 
 int /*<<< orphan*/  meson_mmc_desc_chain_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  meson_mmc_get_transfer_mode (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  meson_mmc_post_req (struct mmc_host*,struct mmc_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_mmc_pre_req (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  meson_mmc_start_cmd (struct mmc_host*,int /*<<< orphan*/ ) ; 
 struct meson_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_mmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct meson_host *host = mmc_priv(mmc);
	bool needs_pre_post_req = mrq->data &&
			!(mrq->data->host_cookie & SD_EMMC_PRE_REQ_DONE);

	if (needs_pre_post_req) {
		meson_mmc_get_transfer_mode(mmc, mrq);
		if (!meson_mmc_desc_chain_mode(mrq->data))
			needs_pre_post_req = false;
	}

	if (needs_pre_post_req)
		meson_mmc_pre_req(mmc, mrq);

	/* Stop execution */
	writel(0, host->regs + SD_EMMC_START);

	meson_mmc_start_cmd(mmc, mrq->sbc ?: mrq->cmd);

	if (needs_pre_post_req)
		meson_mmc_post_req(mmc, mrq, 0);
}