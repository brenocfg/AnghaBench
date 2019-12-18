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
typedef  int u8 ;
struct mmc_command {int opcode; unsigned long arg; unsigned long busy_timeout; int /*<<< orphan*/  data; } ;
struct alcor_sdmmc_host {int /*<<< orphan*/  dev; int /*<<< orphan*/  timeout_work; struct mmc_command* cmd; struct alcor_pci_priv* alcor_pci; } ;
struct alcor_pci_priv {int dummy; } ;

/* Variables and functions */
 int AU6601_CMD_17_BYTE_CRC ; 
 int AU6601_CMD_6_BYTE_CRC ; 
 int AU6601_CMD_6_BYTE_WO_CRC ; 
 int AU6601_CMD_NO_RESP ; 
 int AU6601_CMD_START_XFER ; 
 int AU6601_CMD_STOP_WAIT_RDY ; 
 int /*<<< orphan*/  AU6601_CMD_XFER_CTRL ; 
 int /*<<< orphan*/  AU6601_REG_CMD_ARG ; 
 int /*<<< orphan*/  AU6601_REG_CMD_OPCODE ; 
#define  MMC_RSP_NONE 132 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 int /*<<< orphan*/  alcor_prepare_data (struct alcor_sdmmc_host*,struct mmc_command*) ; 
 int /*<<< orphan*/  alcor_write32be (struct alcor_pci_priv*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcor_write8 (struct alcor_pci_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_from_priv (struct alcor_sdmmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int mmc_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alcor_send_cmd(struct alcor_sdmmc_host *host,
			   struct mmc_command *cmd, bool set_timeout)
{
	struct alcor_pci_priv *priv = host->alcor_pci;
	unsigned long timeout = 0;
	u8 ctrl = 0;

	host->cmd = cmd;
	alcor_prepare_data(host, cmd);

	dev_dbg(host->dev, "send CMD. opcode: 0x%02x, arg; 0x%08x\n",
		cmd->opcode, cmd->arg);
	alcor_write8(priv, cmd->opcode | 0x40, AU6601_REG_CMD_OPCODE);
	alcor_write32be(priv, cmd->arg, AU6601_REG_CMD_ARG);

	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_NONE:
		ctrl = AU6601_CMD_NO_RESP;
		break;
	case MMC_RSP_R1:
		ctrl = AU6601_CMD_6_BYTE_CRC;
		break;
	case MMC_RSP_R1B:
		ctrl = AU6601_CMD_6_BYTE_CRC | AU6601_CMD_STOP_WAIT_RDY;
		break;
	case MMC_RSP_R2:
		ctrl = AU6601_CMD_17_BYTE_CRC;
		break;
	case MMC_RSP_R3:
		ctrl = AU6601_CMD_6_BYTE_WO_CRC;
		break;
	default:
		dev_err(host->dev, "%s: cmd->flag (0x%02x) is not valid\n",
			mmc_hostname(mmc_from_priv(host)), mmc_resp_type(cmd));
		break;
	}

	if (set_timeout) {
		if (!cmd->data && cmd->busy_timeout)
			timeout = cmd->busy_timeout;
		else
			timeout = 10000;

		schedule_delayed_work(&host->timeout_work,
				      msecs_to_jiffies(timeout));
	}

	dev_dbg(host->dev, "xfer ctrl: 0x%02x; timeout: %lu\n", ctrl, timeout);
	alcor_write8(priv, ctrl | AU6601_CMD_START_XFER,
				 AU6601_CMD_XFER_CTRL);
}