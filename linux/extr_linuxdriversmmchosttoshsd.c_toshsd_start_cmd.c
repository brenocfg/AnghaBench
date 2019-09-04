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
struct toshsd_host {scalar_t__ ioaddr; struct mmc_command* cmd; TYPE_1__* pdev; struct mmc_data* data; } ;
struct mmc_data {int blocks; int flags; } ;
struct mmc_command {int opcode; int* resp; int /*<<< orphan*/  arg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MMC_APP_CMD ; 
 int MMC_DATA_READ ; 
 int MMC_GO_IDLE_STATE ; 
#define  MMC_RSP_NONE 132 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 int MMC_STOP_TRANSMISSION ; 
 scalar_t__ SD_ARG0 ; 
 scalar_t__ SD_CMD ; 
 int SD_CMD_DATA_PRESENT ; 
 int SD_CMD_MULTI_BLOCK ; 
 int SD_CMD_RESP_TYPE_EXT_R1 ; 
 int SD_CMD_RESP_TYPE_EXT_R1B ; 
 int SD_CMD_RESP_TYPE_EXT_R2 ; 
 int SD_CMD_RESP_TYPE_EXT_R3 ; 
 int SD_CMD_RESP_TYPE_NONE ; 
 int SD_CMD_TRANSFER_READ ; 
 int SD_CMD_TYPE_ACMD ; 
 scalar_t__ SD_STOPINTERNAL ; 
 int SD_STOPINT_AUTO_ISSUE_CMD12 ; 
 int SD_STOPINT_ISSUE_CMD12 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int mmc_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  toshsd_finish_request (struct toshsd_host*) ; 

__attribute__((used)) static void toshsd_start_cmd(struct toshsd_host *host, struct mmc_command *cmd)
{
	struct mmc_data *data = host->data;
	int c = cmd->opcode;

	dev_dbg(&host->pdev->dev, "Command opcode: %d\n", cmd->opcode);

	if (cmd->opcode == MMC_STOP_TRANSMISSION) {
		iowrite16(SD_STOPINT_ISSUE_CMD12,
			  host->ioaddr + SD_STOPINTERNAL);

		cmd->resp[0] = cmd->opcode;
		cmd->resp[1] = 0;
		cmd->resp[2] = 0;
		cmd->resp[3] = 0;

		toshsd_finish_request(host);
		return;
	}

	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_NONE:
		c |= SD_CMD_RESP_TYPE_NONE;
		break;

	case MMC_RSP_R1:
		c |= SD_CMD_RESP_TYPE_EXT_R1;
		break;
	case MMC_RSP_R1B:
		c |= SD_CMD_RESP_TYPE_EXT_R1B;
		break;
	case MMC_RSP_R2:
		c |= SD_CMD_RESP_TYPE_EXT_R2;
		break;
	case MMC_RSP_R3:
		c |= SD_CMD_RESP_TYPE_EXT_R3;
		break;

	default:
		dev_err(&host->pdev->dev, "Unknown response type %d\n",
			mmc_resp_type(cmd));
		break;
	}

	host->cmd = cmd;

	if (cmd->opcode == MMC_APP_CMD)
		c |= SD_CMD_TYPE_ACMD;

	if (cmd->opcode == MMC_GO_IDLE_STATE)
		c |= (3 << 8);  /* removed from ipaq-asic3.h for some reason */

	if (data) {
		c |= SD_CMD_DATA_PRESENT;

		if (data->blocks > 1) {
			iowrite16(SD_STOPINT_AUTO_ISSUE_CMD12,
				  host->ioaddr + SD_STOPINTERNAL);
			c |= SD_CMD_MULTI_BLOCK;
		}

		if (data->flags & MMC_DATA_READ)
			c |= SD_CMD_TRANSFER_READ;

		/* MMC_DATA_WRITE does not require a bit to be set */
	}

	/* Send the command */
	iowrite32(cmd->arg, host->ioaddr + SD_ARG0);
	iowrite16(c, host->ioaddr + SD_CMD);
}