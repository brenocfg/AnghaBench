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
struct tmio_mmc_host {TYPE_2__* mrq; TYPE_1__* pdata; struct mmc_command* cmd; struct mmc_data* data; } ;
struct mmc_data {int blocks; int flags; } ;
struct mmc_command {int opcode; int /*<<< orphan*/  arg; } ;
struct TYPE_4__ {scalar_t__ sbc; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_ARG_REG ; 
 int /*<<< orphan*/  CTL_SD_CMD ; 
 int /*<<< orphan*/  CTL_STOP_INTERNAL_ACTION ; 
 int DATA_PRESENT ; 
 int EINVAL ; 
 int MMC_DATA_READ ; 
#define  MMC_RSP_NONE 133 
#define  MMC_RSP_R1 132 
#define  MMC_RSP_R1B 131 
#define  MMC_RSP_R1_NO_CRC 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 int NO_CMD12_ISSUE ; 
 int RESP_NONE ; 
 int RESP_R1 ; 
 int RESP_R1B ; 
 int RESP_R2 ; 
 int RESP_R3 ; 
 int SD_IO_RW_EXTENDED ; 
 int /*<<< orphan*/  TMIO_MASK_CMD ; 
 int TMIO_MMC_HAVE_CMD12_CTRL ; 
 int TMIO_STOP_SEC ; 
 int TRANSFER_MULTI ; 
 int TRANSFER_READ ; 
 int mmc_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_ctrl_write32_as_16_and_16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmio_mmc_enable_mmc_irqs (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tmio_mmc_start_command(struct tmio_mmc_host *host,
				  struct mmc_command *cmd)
{
	struct mmc_data *data = host->data;
	int c = cmd->opcode;

	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_NONE: c |= RESP_NONE; break;
	case MMC_RSP_R1:
	case MMC_RSP_R1_NO_CRC:
			   c |= RESP_R1;   break;
	case MMC_RSP_R1B:  c |= RESP_R1B;  break;
	case MMC_RSP_R2:   c |= RESP_R2;   break;
	case MMC_RSP_R3:   c |= RESP_R3;   break;
	default:
		pr_debug("Unknown response type %d\n", mmc_resp_type(cmd));
		return -EINVAL;
	}

	host->cmd = cmd;

/* FIXME - this seems to be ok commented out but the spec suggest this bit
 *         should be set when issuing app commands.
 *	if(cmd->flags & MMC_FLAG_ACMD)
 *		c |= APP_CMD;
 */
	if (data) {
		c |= DATA_PRESENT;
		if (data->blocks > 1) {
			sd_ctrl_write16(host, CTL_STOP_INTERNAL_ACTION, TMIO_STOP_SEC);
			c |= TRANSFER_MULTI;

			/*
			 * Disable auto CMD12 at IO_RW_EXTENDED and
			 * SET_BLOCK_COUNT when doing multiple block transfer
			 */
			if ((host->pdata->flags & TMIO_MMC_HAVE_CMD12_CTRL) &&
			    (cmd->opcode == SD_IO_RW_EXTENDED || host->mrq->sbc))
				c |= NO_CMD12_ISSUE;
		}
		if (data->flags & MMC_DATA_READ)
			c |= TRANSFER_READ;
	}

	tmio_mmc_enable_mmc_irqs(host, TMIO_MASK_CMD);

	/* Fire off the command */
	sd_ctrl_write32_as_16_and_16(host, CTL_ARG_REG, cmd->arg);
	sd_ctrl_write16(host, CTL_SD_CMD, c);

	return 0;
}