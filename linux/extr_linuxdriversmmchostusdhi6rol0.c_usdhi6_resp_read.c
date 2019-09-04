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
typedef  int u32 ;
struct usdhi6_host {int irq_status; int /*<<< orphan*/  mmc; TYPE_1__* mrq; } ;
struct mmc_command {int* resp; scalar_t__ opcode; } ;
struct TYPE_2__ {struct mmc_command* cmd; } ;

/* Variables and functions */
 scalar_t__ MMC_READ_MULTIPLE_BLOCK ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_NONE ; 
 scalar_t__ MMC_WRITE_MULTIPLE_BLOCK ; 
 int USDHI6_SD_INFO1_RSP_END ; 
 scalar_t__ USDHI6_SD_RSP10 ; 
 scalar_t__ USDHI6_SD_RSP54 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int mmc_resp_type (struct mmc_command*) ; 
 int usdhi6_read (struct usdhi6_host*,scalar_t__) ; 

__attribute__((used)) static void usdhi6_resp_read(struct usdhi6_host *host)
{
	struct mmc_command *cmd = host->mrq->cmd;
	u32 *rsp = cmd->resp, tmp = 0;
	int i;

/*
 * RSP10	39-8
 * RSP32	71-40
 * RSP54	103-72
 * RSP76	127-104
 * R2-type response:
 * resp[0]	= r[127..96]
 * resp[1]	= r[95..64]
 * resp[2]	= r[63..32]
 * resp[3]	= r[31..0]
 * Other responses:
 * resp[0]	= r[39..8]
 */

	if (mmc_resp_type(cmd) == MMC_RSP_NONE)
		return;

	if (!(host->irq_status & USDHI6_SD_INFO1_RSP_END)) {
		dev_err(mmc_dev(host->mmc),
			"CMD%d: response expected but is missing!\n", cmd->opcode);
		return;
	}

	if (mmc_resp_type(cmd) & MMC_RSP_136)
		for (i = 0; i < 4; i++) {
			if (i)
				rsp[3 - i] = tmp >> 24;
			tmp = usdhi6_read(host, USDHI6_SD_RSP10 + i * 8);
			rsp[3 - i] |= tmp << 8;
		}
	else if (cmd->opcode == MMC_READ_MULTIPLE_BLOCK ||
		 cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK)
		/* Read RSP54 to avoid conflict with auto CMD12 */
		rsp[0] = usdhi6_read(host, USDHI6_SD_RSP54);
	else
		rsp[0] = usdhi6_read(host, USDHI6_SD_RSP10);

	dev_dbg(mmc_dev(host->mmc), "Response 0x%x\n", rsp[0]);
}