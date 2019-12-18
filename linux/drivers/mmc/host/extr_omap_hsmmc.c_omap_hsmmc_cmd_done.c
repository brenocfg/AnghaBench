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
struct omap_hsmmc_host {int flags; TYPE_2__* mrq; int /*<<< orphan*/  response_busy; int /*<<< orphan*/ * data; int /*<<< orphan*/  base; TYPE_1__* cmd; } ;
struct mmc_command {int flags; scalar_t__ error; void** resp; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cmd; TYPE_1__* sbc; } ;
struct TYPE_3__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int AUTO_CMD23 ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 void* OMAP_HSMMC_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSP10 ; 
 int /*<<< orphan*/  RSP32 ; 
 int /*<<< orphan*/  RSP54 ; 
 int /*<<< orphan*/  RSP76 ; 
 int /*<<< orphan*/  omap_hsmmc_request_done (struct omap_hsmmc_host*,TYPE_2__*) ; 
 int /*<<< orphan*/  omap_hsmmc_start_command (struct omap_hsmmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hsmmc_start_dma_transfer (struct omap_hsmmc_host*) ; 

__attribute__((used)) static void
omap_hsmmc_cmd_done(struct omap_hsmmc_host *host, struct mmc_command *cmd)
{
	if (host->mrq->sbc && (host->cmd == host->mrq->sbc) &&
	    !host->mrq->sbc->error && !(host->flags & AUTO_CMD23)) {
		host->cmd = NULL;
		omap_hsmmc_start_dma_transfer(host);
		omap_hsmmc_start_command(host, host->mrq->cmd,
						host->mrq->data);
		return;
	}

	host->cmd = NULL;

	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			/* response type 2 */
			cmd->resp[3] = OMAP_HSMMC_READ(host->base, RSP10);
			cmd->resp[2] = OMAP_HSMMC_READ(host->base, RSP32);
			cmd->resp[1] = OMAP_HSMMC_READ(host->base, RSP54);
			cmd->resp[0] = OMAP_HSMMC_READ(host->base, RSP76);
		} else {
			/* response types 1, 1b, 3, 4, 5, 6 */
			cmd->resp[0] = OMAP_HSMMC_READ(host->base, RSP10);
		}
	}
	if ((host->data == NULL && !host->response_busy) || cmd->error)
		omap_hsmmc_request_done(host, host->mrq);
}