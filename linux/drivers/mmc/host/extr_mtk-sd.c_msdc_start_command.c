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
typedef  int /*<<< orphan*/  u32 ;
struct msdc_host {scalar_t__ base; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  req_timeout; struct mmc_command* cmd; } ;
struct mmc_request {int dummy; } ;
struct mmc_command {int /*<<< orphan*/  arg; scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAT_TIMEOUT ; 
 scalar_t__ MSDC_FIFOCS ; 
 int MSDC_FIFOCS_RXCNT ; 
 int MSDC_FIFOCS_TXCNT ; 
 scalar_t__ MSDC_INTEN ; 
 scalar_t__ SDC_ARG ; 
 scalar_t__ SDC_CMD ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_command*) ; 
 int /*<<< orphan*/  cmd_ints_mask ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msdc_cmd_is_ready (struct msdc_host*,struct mmc_request*,struct mmc_command*) ; 
 int /*<<< orphan*/  msdc_cmd_prepare_raw_cmd (struct msdc_host*,struct mmc_request*,struct mmc_command*) ; 
 int /*<<< orphan*/  msdc_reset_hw (struct msdc_host*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sdr_set_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_wq ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void msdc_start_command(struct msdc_host *host,
		struct mmc_request *mrq, struct mmc_command *cmd)
{
	u32 rawcmd;
	unsigned long flags;

	WARN_ON(host->cmd);
	host->cmd = cmd;

	mod_delayed_work(system_wq, &host->req_timeout, DAT_TIMEOUT);
	if (!msdc_cmd_is_ready(host, mrq, cmd))
		return;

	if ((readl(host->base + MSDC_FIFOCS) & MSDC_FIFOCS_TXCNT) >> 16 ||
	    readl(host->base + MSDC_FIFOCS) & MSDC_FIFOCS_RXCNT) {
		dev_err(host->dev, "TX/RX FIFO non-empty before start of IO. Reset\n");
		msdc_reset_hw(host);
	}

	cmd->error = 0;
	rawcmd = msdc_cmd_prepare_raw_cmd(host, mrq, cmd);

	spin_lock_irqsave(&host->lock, flags);
	sdr_set_bits(host->base + MSDC_INTEN, cmd_ints_mask);
	spin_unlock_irqrestore(&host->lock, flags);

	writel(cmd->arg, host->base + SDC_ARG);
	writel(rawcmd, host->base + SDC_CMD);
}