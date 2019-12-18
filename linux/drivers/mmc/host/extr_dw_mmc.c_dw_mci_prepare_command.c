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
struct mmc_host {int dummy; } ;
struct mmc_command {int opcode; int arg; int flags; TYPE_1__* data; int /*<<< orphan*/  error; } ;
struct dw_mci_slot {int id; int /*<<< orphan*/  flags; struct dw_mci* host; } ;
struct dw_mci {scalar_t__ state; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKENA ; 
 int /*<<< orphan*/  DW_MMC_CARD_NO_USE_HOLD ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int MMC_DATA_WRITE ; 
 scalar_t__ MMC_GO_IDLE_STATE ; 
 scalar_t__ MMC_GO_INACTIVE_STATE ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_CRC ; 
 int MMC_RSP_PRESENT ; 
 scalar_t__ MMC_SEND_STATUS ; 
 scalar_t__ MMC_STOP_TRANSMISSION ; 
 int SDIO_CCCR_ABORT ; 
 int SDMMC_CLKEN_LOW_PWR ; 
 int SDMMC_CMD_DAT_EXP ; 
 int SDMMC_CMD_DAT_WR ; 
 int SDMMC_CMD_PRV_DAT_WAIT ; 
 int SDMMC_CMD_RESP_CRC ; 
 int SDMMC_CMD_RESP_EXP ; 
 int SDMMC_CMD_RESP_LONG ; 
 int SDMMC_CMD_STOP ; 
 int SDMMC_CMD_UPD_CLK ; 
 int SDMMC_CMD_USE_HOLD_REG ; 
 int SDMMC_CMD_VOLT_SWITCH ; 
 scalar_t__ SD_IO_RW_DIRECT ; 
 scalar_t__ SD_SWITCH_VOLTAGE ; 
 scalar_t__ STATE_SENDING_CMD ; 
 scalar_t__ STATE_SENDING_CMD11 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int mci_readl (struct dw_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_send_cmd (struct dw_mci_slot*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 
 struct dw_mci_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 dw_mci_prepare_command(struct mmc_host *mmc, struct mmc_command *cmd)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;
	u32 cmdr;

	cmd->error = -EINPROGRESS;
	cmdr = cmd->opcode;

	if (cmd->opcode == MMC_STOP_TRANSMISSION ||
	    cmd->opcode == MMC_GO_IDLE_STATE ||
	    cmd->opcode == MMC_GO_INACTIVE_STATE ||
	    (cmd->opcode == SD_IO_RW_DIRECT &&
	     ((cmd->arg >> 9) & 0x1FFFF) == SDIO_CCCR_ABORT))
		cmdr |= SDMMC_CMD_STOP;
	else if (cmd->opcode != MMC_SEND_STATUS && cmd->data)
		cmdr |= SDMMC_CMD_PRV_DAT_WAIT;

	if (cmd->opcode == SD_SWITCH_VOLTAGE) {
		u32 clk_en_a;

		/* Special bit makes CMD11 not die */
		cmdr |= SDMMC_CMD_VOLT_SWITCH;

		/* Change state to continue to handle CMD11 weirdness */
		WARN_ON(slot->host->state != STATE_SENDING_CMD);
		slot->host->state = STATE_SENDING_CMD11;

		/*
		 * We need to disable low power mode (automatic clock stop)
		 * while doing voltage switch so we don't confuse the card,
		 * since stopping the clock is a specific part of the UHS
		 * voltage change dance.
		 *
		 * Note that low power mode (SDMMC_CLKEN_LOW_PWR) will be
		 * unconditionally turned back on in dw_mci_setup_bus() if it's
		 * ever called with a non-zero clock.  That shouldn't happen
		 * until the voltage change is all done.
		 */
		clk_en_a = mci_readl(host, CLKENA);
		clk_en_a &= ~(SDMMC_CLKEN_LOW_PWR << slot->id);
		mci_writel(host, CLKENA, clk_en_a);
		mci_send_cmd(slot, SDMMC_CMD_UPD_CLK |
			     SDMMC_CMD_PRV_DAT_WAIT, 0);
	}

	if (cmd->flags & MMC_RSP_PRESENT) {
		/* We expect a response, so set this bit */
		cmdr |= SDMMC_CMD_RESP_EXP;
		if (cmd->flags & MMC_RSP_136)
			cmdr |= SDMMC_CMD_RESP_LONG;
	}

	if (cmd->flags & MMC_RSP_CRC)
		cmdr |= SDMMC_CMD_RESP_CRC;

	if (cmd->data) {
		cmdr |= SDMMC_CMD_DAT_EXP;
		if (cmd->data->flags & MMC_DATA_WRITE)
			cmdr |= SDMMC_CMD_DAT_WR;
	}

	if (!test_bit(DW_MMC_CARD_NO_USE_HOLD, &slot->flags))
		cmdr |= SDMMC_CMD_USE_HOLD_REG;

	return cmdr;
}