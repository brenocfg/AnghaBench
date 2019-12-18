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
struct mmc_request {TYPE_1__* cmd; } ;
struct mmc_host {int dummy; } ;
struct alcor_sdmmc_host {int /*<<< orphan*/  cmd_mutex; struct mmc_request* mrq; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEDIUM ; 
 scalar_t__ alcor_get_cd (struct mmc_host*) ; 
 int /*<<< orphan*/  alcor_request_complete (struct alcor_sdmmc_host*,int) ; 
 int /*<<< orphan*/  alcor_send_cmd (struct alcor_sdmmc_host*,TYPE_1__*,int) ; 
 struct alcor_sdmmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alcor_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct alcor_sdmmc_host *host = mmc_priv(mmc);

	mutex_lock(&host->cmd_mutex);

	host->mrq = mrq;

	/* check if card is present then send command and data */
	if (alcor_get_cd(mmc))
		alcor_send_cmd(host, mrq->cmd, true);
	else {
		mrq->cmd->error = -ENOMEDIUM;
		alcor_request_complete(host, 1);
	}

	mutex_unlock(&host->cmd_mutex);
}