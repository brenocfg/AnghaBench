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
struct msdc_host {int cmd_rsp; scalar_t__ timeout_ns; scalar_t__ timeout_clks; scalar_t__ base; TYPE_1__* mmc; } ;
struct mmc_request {TYPE_2__* sbc; } ;
struct mmc_data {int blksz; int flags; int blocks; scalar_t__ timeout_ns; scalar_t__ timeout_clks; } ;
struct mmc_command {int opcode; unsigned int flags; struct mmc_data* data; } ;
struct TYPE_4__ {int arg; } ;
struct TYPE_3__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 scalar_t__ MMC_CMD_ADTC ; 
 int MMC_DATA_WRITE ; 
 int MMC_SEND_EXT_CSD ; 
 int MMC_STOP_TRANSMISSION ; 
 scalar_t__ MSDC_CFG ; 
 int /*<<< orphan*/  MSDC_CFG_PIO ; 
 scalar_t__ SDC_BLK_NUM ; 
 int SD_APP_SD_STATUS ; 
 int SD_APP_SEND_NUM_WR_BLKS ; 
 int SD_APP_SEND_SCR ; 
 int SD_IO_RW_DIRECT ; 
 int SD_SWITCH ; 
 int SD_SWITCH_VOLTAGE ; 
 scalar_t__ mmc_card_mmc (int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_cmd_type (struct mmc_command*) ; 
 scalar_t__ mmc_op_multi (int) ; 
 int msdc_cmd_find_resp (struct msdc_host*,struct mmc_request*,struct mmc_command*) ; 
 int /*<<< orphan*/  msdc_set_timeout (struct msdc_host*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sdr_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline u32 msdc_cmd_prepare_raw_cmd(struct msdc_host *host,
		struct mmc_request *mrq, struct mmc_command *cmd)
{
	/* rawcmd :
	 * vol_swt << 30 | auto_cmd << 28 | blklen << 16 | go_irq << 15 |
	 * stop << 14 | rw << 13 | dtype << 11 | rsptyp << 7 | brk << 6 | opcode
	 */
	u32 opcode = cmd->opcode;
	u32 resp = msdc_cmd_find_resp(host, mrq, cmd);
	u32 rawcmd = (opcode & 0x3f) | ((resp & 0x7) << 7);

	host->cmd_rsp = resp;

	if ((opcode == SD_IO_RW_DIRECT && cmd->flags == (unsigned int) -1) ||
	    opcode == MMC_STOP_TRANSMISSION)
		rawcmd |= (0x1 << 14);
	else if (opcode == SD_SWITCH_VOLTAGE)
		rawcmd |= (0x1 << 30);
	else if (opcode == SD_APP_SEND_SCR ||
		 opcode == SD_APP_SEND_NUM_WR_BLKS ||
		 (opcode == SD_SWITCH && mmc_cmd_type(cmd) == MMC_CMD_ADTC) ||
		 (opcode == SD_APP_SD_STATUS && mmc_cmd_type(cmd) == MMC_CMD_ADTC) ||
		 (opcode == MMC_SEND_EXT_CSD && mmc_cmd_type(cmd) == MMC_CMD_ADTC))
		rawcmd |= (0x1 << 11);

	if (cmd->data) {
		struct mmc_data *data = cmd->data;

		if (mmc_op_multi(opcode)) {
			if (mmc_card_mmc(host->mmc->card) && mrq->sbc &&
			    !(mrq->sbc->arg & 0xFFFF0000))
				rawcmd |= 0x2 << 28; /* AutoCMD23 */
		}

		rawcmd |= ((data->blksz & 0xFFF) << 16);
		if (data->flags & MMC_DATA_WRITE)
			rawcmd |= (0x1 << 13);
		if (data->blocks > 1)
			rawcmd |= (0x2 << 11);
		else
			rawcmd |= (0x1 << 11);
		/* Always use dma mode */
		sdr_clr_bits(host->base + MSDC_CFG, MSDC_CFG_PIO);

		if (host->timeout_ns != data->timeout_ns ||
		    host->timeout_clks != data->timeout_clks)
			msdc_set_timeout(host, data->timeout_ns,
					data->timeout_clks);

		writel(data->blocks, host->base + SDC_BLK_NUM);
	}
	return rawcmd;
}