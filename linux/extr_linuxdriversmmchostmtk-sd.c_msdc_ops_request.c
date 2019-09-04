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
struct msdc_host {struct mmc_request* mrq; scalar_t__ error; } ;
struct mmc_request {TYPE_1__* cmd; TYPE_1__* sbc; scalar_t__ data; } ;
struct mmc_host {int /*<<< orphan*/  card; } ;
struct TYPE_2__ {int arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_card_mmc (int /*<<< orphan*/ ) ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  msdc_prepare_data (struct msdc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  msdc_start_command (struct msdc_host*,struct mmc_request*,TYPE_1__*) ; 

__attribute__((used)) static void msdc_ops_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct msdc_host *host = mmc_priv(mmc);

	host->error = 0;
	WARN_ON(host->mrq);
	host->mrq = mrq;

	if (mrq->data)
		msdc_prepare_data(host, mrq);

	/* if SBC is required, we have HW option and SW option.
	 * if HW option is enabled, and SBC does not have "special" flags,
	 * use HW option,  otherwise use SW option
	 */
	if (mrq->sbc && (!mmc_card_mmc(mmc->card) ||
	    (mrq->sbc->arg & 0xFFFF0000)))
		msdc_start_command(host, mrq, mrq->sbc);
	else
		msdc_start_command(host, mrq, mrq->cmd);
}