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
struct mxs_mmc_host {struct mmc_request* mrq; } ;
struct mmc_request {int /*<<< orphan*/  cmd; int /*<<< orphan*/  sbc; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct mxs_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mxs_mmc_start_cmd (struct mxs_mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxs_mmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct mxs_mmc_host *host = mmc_priv(mmc);

	WARN_ON(host->mrq != NULL);
	host->mrq = mrq;

	if (mrq->sbc)
		mxs_mmc_start_cmd(host, mrq->sbc);
	else
		mxs_mmc_start_cmd(host, mrq->cmd);
}