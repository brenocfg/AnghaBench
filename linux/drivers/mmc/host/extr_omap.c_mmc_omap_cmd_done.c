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
struct mmc_omap_host {int /*<<< orphan*/  current_slot; struct mmc_host* mmc; int /*<<< orphan*/ * mrq; int /*<<< orphan*/ * data; int /*<<< orphan*/  cmd_abort_timer; int /*<<< orphan*/ * cmd; } ;
struct mmc_host {int dummy; } ;
struct mmc_command {int flags; int* resp; int /*<<< orphan*/  mrq; scalar_t__ error; } ;

/* Variables and functions */
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 int OMAP_MMC_READ (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSP0 ; 
 int /*<<< orphan*/  RSP1 ; 
 int /*<<< orphan*/  RSP2 ; 
 int /*<<< orphan*/  RSP3 ; 
 int /*<<< orphan*/  RSP4 ; 
 int /*<<< orphan*/  RSP5 ; 
 int /*<<< orphan*/  RSP6 ; 
 int /*<<< orphan*/  RSP7 ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_omap_abort_xfer (struct mmc_omap_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_omap_release_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmc_omap_cmd_done(struct mmc_omap_host *host, struct mmc_command *cmd)
{
	host->cmd = NULL;

	del_timer(&host->cmd_abort_timer);

	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			/* response type 2 */
			cmd->resp[3] =
				OMAP_MMC_READ(host, RSP0) |
				(OMAP_MMC_READ(host, RSP1) << 16);
			cmd->resp[2] =
				OMAP_MMC_READ(host, RSP2) |
				(OMAP_MMC_READ(host, RSP3) << 16);
			cmd->resp[1] =
				OMAP_MMC_READ(host, RSP4) |
				(OMAP_MMC_READ(host, RSP5) << 16);
			cmd->resp[0] =
				OMAP_MMC_READ(host, RSP6) |
				(OMAP_MMC_READ(host, RSP7) << 16);
		} else {
			/* response types 1, 1b, 3, 4, 5, 6 */
			cmd->resp[0] =
				OMAP_MMC_READ(host, RSP6) |
				(OMAP_MMC_READ(host, RSP7) << 16);
		}
	}

	if (host->data == NULL || cmd->error) {
		struct mmc_host *mmc;

		if (host->data != NULL)
			mmc_omap_abort_xfer(host, host->data);
		host->mrq = NULL;
		mmc = host->mmc;
		mmc_omap_release_slot(host->current_slot, 1);
		mmc_request_done(mmc, cmd->mrq);
	}
}