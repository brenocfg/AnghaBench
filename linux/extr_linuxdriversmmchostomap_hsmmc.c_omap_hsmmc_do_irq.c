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
typedef  int u32 ;
struct omap_hsmmc_host {TYPE_2__* mrq; scalar_t__ cmd; int /*<<< orphan*/  base; int /*<<< orphan*/  mmc; scalar_t__ response_busy; struct mmc_data* data; } ;
struct mmc_data {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sbc; } ;
struct TYPE_3__ {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC12 ; 
 int ACCE ; 
 int ACEB ; 
 int ACE_EN ; 
 int ACIE ; 
 int ACNE ; 
 int ACTO ; 
 int BADA_EN ; 
 int CCRC_EN ; 
 int CC_EN ; 
 int CEB_EN ; 
 int CTO_EN ; 
 int DCRC_EN ; 
 int DEB_EN ; 
 int DTO_EN ; 
 int EILSEQ ; 
 int ERR_EN ; 
 int ETIMEDOUT ; 
 int OMAP_HSMMC_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STAT ; 
 int TC_EN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hsmmc_command_incomplete (struct omap_hsmmc_host*,int,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hsmmc_cmd_done (struct omap_hsmmc_host*,scalar_t__) ; 
 int /*<<< orphan*/  omap_hsmmc_dbg_report_irq (struct omap_hsmmc_host*,int) ; 
 int /*<<< orphan*/  omap_hsmmc_xfer_done (struct omap_hsmmc_host*,struct mmc_data*) ; 

__attribute__((used)) static void omap_hsmmc_do_irq(struct omap_hsmmc_host *host, int status)
{
	struct mmc_data *data;
	int end_cmd = 0, end_trans = 0;
	int error = 0;

	data = host->data;
	dev_vdbg(mmc_dev(host->mmc), "IRQ Status is %x\n", status);

	if (status & ERR_EN) {
		omap_hsmmc_dbg_report_irq(host, status);

		if (status & (CTO_EN | CCRC_EN | CEB_EN))
			end_cmd = 1;
		if (host->data || host->response_busy) {
			end_trans = !end_cmd;
			host->response_busy = 0;
		}
		if (status & (CTO_EN | DTO_EN))
			hsmmc_command_incomplete(host, -ETIMEDOUT, end_cmd);
		else if (status & (CCRC_EN | DCRC_EN | DEB_EN | CEB_EN |
				   BADA_EN))
			hsmmc_command_incomplete(host, -EILSEQ, end_cmd);

		if (status & ACE_EN) {
			u32 ac12;
			ac12 = OMAP_HSMMC_READ(host->base, AC12);
			if (!(ac12 & ACNE) && host->mrq->sbc) {
				end_cmd = 1;
				if (ac12 & ACTO)
					error =  -ETIMEDOUT;
				else if (ac12 & (ACCE | ACEB | ACIE))
					error = -EILSEQ;
				host->mrq->sbc->error = error;
				hsmmc_command_incomplete(host, error, end_cmd);
			}
			dev_dbg(mmc_dev(host->mmc), "AC12 err: 0x%x\n", ac12);
		}
	}

	OMAP_HSMMC_WRITE(host->base, STAT, status);
	if (end_cmd || ((status & CC_EN) && host->cmd))
		omap_hsmmc_cmd_done(host, host->cmd);
	if ((end_trans || (status & TC_EN)) && host->mrq)
		omap_hsmmc_xfer_done(host, data);
}