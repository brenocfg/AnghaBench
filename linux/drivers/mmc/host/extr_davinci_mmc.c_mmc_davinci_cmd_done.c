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
struct mmc_davinci_host {int active_request; scalar_t__ base; int /*<<< orphan*/  mmc; int /*<<< orphan*/ * data; int /*<<< orphan*/ * cmd; } ;
struct mmc_command {int flags; TYPE_2__* mrq; int /*<<< orphan*/  error; void** resp; } ;
struct TYPE_4__ {TYPE_1__* cmd; } ;
struct TYPE_3__ {scalar_t__ retries; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MMCIM ; 
 scalar_t__ DAVINCI_MMCRSP01 ; 
 scalar_t__ DAVINCI_MMCRSP23 ; 
 scalar_t__ DAVINCI_MMCRSP45 ; 
 scalar_t__ DAVINCI_MMCRSP67 ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mmc_davinci_cmd_done(struct mmc_davinci_host *host,
				 struct mmc_command *cmd)
{
	host->cmd = NULL;

	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			/* response type 2 */
			cmd->resp[3] = readl(host->base + DAVINCI_MMCRSP01);
			cmd->resp[2] = readl(host->base + DAVINCI_MMCRSP23);
			cmd->resp[1] = readl(host->base + DAVINCI_MMCRSP45);
			cmd->resp[0] = readl(host->base + DAVINCI_MMCRSP67);
		} else {
			/* response types 1, 1b, 3, 4, 5, 6 */
			cmd->resp[0] = readl(host->base + DAVINCI_MMCRSP67);
		}
	}

	if (host->data == NULL || cmd->error) {
		if (cmd->error == -ETIMEDOUT)
			cmd->mrq->cmd->retries = 0;
		mmc_request_done(host->mmc, cmd->mrq);
		writel(0, host->base + DAVINCI_MMCIM);
		host->active_request = false;
	}
}