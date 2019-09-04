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
typedef  int u16 ;
struct mmc_omap_host {int /*<<< orphan*/  cmd_abort_timer; TYPE_2__* data; TYPE_1__* current_slot; int /*<<< orphan*/  mmc; struct mmc_command* cmd; } ;
struct mmc_command {int opcode; int flags; int arg; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {scalar_t__ bus_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARGH ; 
 int /*<<< orphan*/  ARGL ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  CTO ; 
 int HZ ; 
 int /*<<< orphan*/  IE ; 
 scalar_t__ MMC_BUSMODE_OPENDRAIN ; 
 scalar_t__ MMC_CMD_ADTC ; 
 scalar_t__ MMC_CMD_BC ; 
 scalar_t__ MMC_CMD_BCR ; 
 int MMC_DATA_WRITE ; 
 int MMC_ERASE ; 
 int MMC_RSP_BUSY ; 
#define  MMC_RSP_NONE 132 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 int OMAP_MMC_CMDTYPE_AC ; 
 int OMAP_MMC_CMDTYPE_ADTC ; 
 int OMAP_MMC_CMDTYPE_BC ; 
 int OMAP_MMC_CMDTYPE_BCR ; 
 int OMAP_MMC_STAT_A_EMPTY ; 
 int OMAP_MMC_STAT_A_FULL ; 
 int OMAP_MMC_STAT_CARD_ERR ; 
 int OMAP_MMC_STAT_CMD_CRC ; 
 int OMAP_MMC_STAT_CMD_TOUT ; 
 int OMAP_MMC_STAT_DATA_CRC ; 
 int OMAP_MMC_STAT_DATA_TOUT ; 
 int OMAP_MMC_STAT_END_OF_CMD ; 
 int OMAP_MMC_STAT_END_OF_DATA ; 
 int /*<<< orphan*/  OMAP_MMC_WRITE (struct mmc_omap_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ mmc_cmd_type (struct mmc_command*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int mmc_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
mmc_omap_start_command(struct mmc_omap_host *host, struct mmc_command *cmd)
{
	u32 cmdreg;
	u32 resptype;
	u32 cmdtype;
	u16 irq_mask;

	host->cmd = cmd;

	resptype = 0;
	cmdtype = 0;

	/* Our hardware needs to know exact type */
	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_NONE:
		break;
	case MMC_RSP_R1:
	case MMC_RSP_R1B:
		/* resp 1, 1b, 6, 7 */
		resptype = 1;
		break;
	case MMC_RSP_R2:
		resptype = 2;
		break;
	case MMC_RSP_R3:
		resptype = 3;
		break;
	default:
		dev_err(mmc_dev(host->mmc), "Invalid response type: %04x\n", mmc_resp_type(cmd));
		break;
	}

	if (mmc_cmd_type(cmd) == MMC_CMD_ADTC) {
		cmdtype = OMAP_MMC_CMDTYPE_ADTC;
	} else if (mmc_cmd_type(cmd) == MMC_CMD_BC) {
		cmdtype = OMAP_MMC_CMDTYPE_BC;
	} else if (mmc_cmd_type(cmd) == MMC_CMD_BCR) {
		cmdtype = OMAP_MMC_CMDTYPE_BCR;
	} else {
		cmdtype = OMAP_MMC_CMDTYPE_AC;
	}

	cmdreg = cmd->opcode | (resptype << 8) | (cmdtype << 12);

	if (host->current_slot->bus_mode == MMC_BUSMODE_OPENDRAIN)
		cmdreg |= 1 << 6;

	if (cmd->flags & MMC_RSP_BUSY)
		cmdreg |= 1 << 11;

	if (host->data && !(host->data->flags & MMC_DATA_WRITE))
		cmdreg |= 1 << 15;

	mod_timer(&host->cmd_abort_timer, jiffies + HZ/2);

	OMAP_MMC_WRITE(host, CTO, 200);
	OMAP_MMC_WRITE(host, ARGL, cmd->arg & 0xffff);
	OMAP_MMC_WRITE(host, ARGH, cmd->arg >> 16);
	irq_mask = OMAP_MMC_STAT_A_EMPTY    | OMAP_MMC_STAT_A_FULL    |
		   OMAP_MMC_STAT_CMD_CRC    | OMAP_MMC_STAT_CMD_TOUT  |
		   OMAP_MMC_STAT_DATA_CRC   | OMAP_MMC_STAT_DATA_TOUT |
		   OMAP_MMC_STAT_END_OF_CMD | OMAP_MMC_STAT_CARD_ERR  |
		   OMAP_MMC_STAT_END_OF_DATA;
	if (cmd->opcode == MMC_ERASE)
		irq_mask &= ~OMAP_MMC_STAT_DATA_TOUT;
	OMAP_MMC_WRITE(host, IE, irq_mask);
	OMAP_MMC_WRITE(host, CMD, cmdreg);
}