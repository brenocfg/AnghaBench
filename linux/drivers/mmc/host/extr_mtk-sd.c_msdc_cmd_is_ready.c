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
struct msdc_host {int /*<<< orphan*/  error; int /*<<< orphan*/  dev; scalar_t__ base; } ;
struct mmc_request {int dummy; } ;
struct mmc_command {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ MMC_RSP_R1B ; 
 int /*<<< orphan*/  MSDC_INT_CMDTMO ; 
 int /*<<< orphan*/  REQ_CMD_BUSY ; 
 scalar_t__ SDC_STS ; 
 int SDC_STS_CMDBUSY ; 
 int SDC_STS_SDCBUSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 scalar_t__ mmc_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  msdc_cmd_done (struct msdc_host*,int /*<<< orphan*/ ,struct mmc_request*,struct mmc_command*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static inline bool msdc_cmd_is_ready(struct msdc_host *host,
		struct mmc_request *mrq, struct mmc_command *cmd)
{
	/* The max busy time we can endure is 20ms */
	unsigned long tmo = jiffies + msecs_to_jiffies(20);

	while ((readl(host->base + SDC_STS) & SDC_STS_CMDBUSY) &&
			time_before(jiffies, tmo))
		cpu_relax();
	if (readl(host->base + SDC_STS) & SDC_STS_CMDBUSY) {
		dev_err(host->dev, "CMD bus busy detected\n");
		host->error |= REQ_CMD_BUSY;
		msdc_cmd_done(host, MSDC_INT_CMDTMO, mrq, cmd);
		return false;
	}

	if (mmc_resp_type(cmd) == MMC_RSP_R1B || cmd->data) {
		tmo = jiffies + msecs_to_jiffies(20);
		/* R1B or with data, should check SDCBUSY */
		while ((readl(host->base + SDC_STS) & SDC_STS_SDCBUSY) &&
				time_before(jiffies, tmo))
			cpu_relax();
		if (readl(host->base + SDC_STS) & SDC_STS_SDCBUSY) {
			dev_err(host->dev, "Controller busy detected\n");
			host->error |= REQ_CMD_BUSY;
			msdc_cmd_done(host, MSDC_INT_CMDTMO, mrq, cmd);
			return false;
		}
	}
	return true;
}