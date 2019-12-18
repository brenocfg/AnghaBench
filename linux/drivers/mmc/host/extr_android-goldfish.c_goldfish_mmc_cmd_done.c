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
struct mmc_command {int flags; int /*<<< orphan*/  mrq; scalar_t__ error; void** resp; } ;
struct goldfish_mmc_host {int /*<<< orphan*/ * mrq; int /*<<< orphan*/ * data; int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 void* GOLDFISH_MMC_READ (struct goldfish_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_RESP_0 ; 
 int /*<<< orphan*/  MMC_RESP_1 ; 
 int /*<<< orphan*/  MMC_RESP_2 ; 
 int /*<<< orphan*/  MMC_RESP_3 ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 int /*<<< orphan*/  mmc_from_priv (struct goldfish_mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void goldfish_mmc_cmd_done(struct goldfish_mmc_host *host,
				  struct mmc_command *cmd)
{
	host->cmd = NULL;
	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			/* response type 2 */
			cmd->resp[3] =
				GOLDFISH_MMC_READ(host, MMC_RESP_0);
			cmd->resp[2] =
				GOLDFISH_MMC_READ(host, MMC_RESP_1);
			cmd->resp[1] =
				GOLDFISH_MMC_READ(host, MMC_RESP_2);
			cmd->resp[0] =
				GOLDFISH_MMC_READ(host, MMC_RESP_3);
		} else {
			/* response types 1, 1b, 3, 4, 5, 6 */
			cmd->resp[0] =
				GOLDFISH_MMC_READ(host, MMC_RESP_0);
		}
	}

	if (host->data == NULL || cmd->error) {
		host->mrq = NULL;
		mmc_request_done(mmc_from_priv(host), cmd->mrq);
	}
}