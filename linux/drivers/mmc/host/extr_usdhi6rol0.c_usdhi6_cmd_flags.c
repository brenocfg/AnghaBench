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
typedef  int u16 ;
struct usdhi6_host {int app_cmd; int /*<<< orphan*/  mmc; struct mmc_request* mrq; } ;
struct mmc_request {int /*<<< orphan*/  stop; TYPE_1__* data; struct mmc_command* cmd; } ;
struct mmc_command {int opcode; } ;
struct TYPE_2__ {int flags; int blocks; } ;

/* Variables and functions */
 int EINVAL ; 
 int MMC_DATA_READ ; 
 scalar_t__ MMC_READ_MULTIPLE_BLOCK ; 
#define  MMC_RSP_NONE 132 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 scalar_t__ MMC_WRITE_MULTIPLE_BLOCK ; 
 scalar_t__ SD_IO_RW_EXTENDED ; 
 int USDHI6_SD_CMD_APP ; 
 int USDHI6_SD_CMD_CMD12_AUTO_OFF ; 
 int USDHI6_SD_CMD_DATA ; 
 int USDHI6_SD_CMD_MODE_RSP_NONE ; 
 int USDHI6_SD_CMD_MODE_RSP_R1 ; 
 int USDHI6_SD_CMD_MODE_RSP_R1B ; 
 int USDHI6_SD_CMD_MODE_RSP_R2 ; 
 int USDHI6_SD_CMD_MODE_RSP_R3 ; 
 int USDHI6_SD_CMD_MULTI ; 
 int USDHI6_SD_CMD_READ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int mmc_resp_type (struct mmc_command*) ; 

__attribute__((used)) static int usdhi6_cmd_flags(struct usdhi6_host *host)
{
	struct mmc_request *mrq = host->mrq;
	struct mmc_command *cmd = mrq->cmd;
	u16 opc = cmd->opcode;

	if (host->app_cmd) {
		host->app_cmd = false;
		opc |= USDHI6_SD_CMD_APP;
	}

	if (mrq->data) {
		opc |= USDHI6_SD_CMD_DATA;

		if (mrq->data->flags & MMC_DATA_READ)
			opc |= USDHI6_SD_CMD_READ;

		if (cmd->opcode == MMC_READ_MULTIPLE_BLOCK ||
		    cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK ||
		    (cmd->opcode == SD_IO_RW_EXTENDED &&
		     mrq->data->blocks > 1)) {
			opc |= USDHI6_SD_CMD_MULTI;
			if (!mrq->stop)
				opc |= USDHI6_SD_CMD_CMD12_AUTO_OFF;
		}

		switch (mmc_resp_type(cmd)) {
		case MMC_RSP_NONE:
			opc |= USDHI6_SD_CMD_MODE_RSP_NONE;
			break;
		case MMC_RSP_R1:
			opc |= USDHI6_SD_CMD_MODE_RSP_R1;
			break;
		case MMC_RSP_R1B:
			opc |= USDHI6_SD_CMD_MODE_RSP_R1B;
			break;
		case MMC_RSP_R2:
			opc |= USDHI6_SD_CMD_MODE_RSP_R2;
			break;
		case MMC_RSP_R3:
			opc |= USDHI6_SD_CMD_MODE_RSP_R3;
			break;
		default:
			dev_warn(mmc_dev(host->mmc),
				 "Unknown response type %d\n",
				 mmc_resp_type(cmd));
			return -EINVAL;
		}
	}

	return opc;
}