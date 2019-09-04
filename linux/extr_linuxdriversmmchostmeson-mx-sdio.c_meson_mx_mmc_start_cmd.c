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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ bus_width; } ;
struct mmc_host {TYPE_1__ ios; } ;
struct mmc_command {int busy_timeout; int flags; int opcode; int /*<<< orphan*/  arg; TYPE_2__* data; } ;
struct meson_mx_mmc_host {int slot_id; int /*<<< orphan*/  cmd_timeout; int /*<<< orphan*/  irq_lock; scalar_t__ base; struct mmc_command* cmd; } ;
struct TYPE_4__ {int blocks; unsigned int blksz; int flags; scalar_t__ bytes_xfered; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 unsigned int BITS_PER_BYTE ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MESON_MX_SDIO_ARGU ; 
 scalar_t__ MESON_MX_SDIO_EXT ; 
 int /*<<< orphan*/  MESON_MX_SDIO_EXT_DATA_RW_NUMBER_MASK ; 
 int /*<<< orphan*/  MESON_MX_SDIO_IRQC ; 
 int /*<<< orphan*/  MESON_MX_SDIO_IRQC_ARC_CMD_INT_EN ; 
 int /*<<< orphan*/  MESON_MX_SDIO_IRQS ; 
 int /*<<< orphan*/  MESON_MX_SDIO_IRQS_CMD_INT ; 
 scalar_t__ MESON_MX_SDIO_MULT ; 
 int /*<<< orphan*/  MESON_MX_SDIO_MULT_PORT_SEL_MASK ; 
 int MESON_MX_SDIO_RESPONSE_CRC16_BITS ; 
 scalar_t__ MESON_MX_SDIO_SEND ; 
 int /*<<< orphan*/  MESON_MX_SDIO_SEND_CHECK_DAT0_BUSY ; 
 int /*<<< orphan*/  MESON_MX_SDIO_SEND_CMD_RESP_BITS_MASK ; 
 int /*<<< orphan*/  MESON_MX_SDIO_SEND_COMMAND_INDEX_MASK ; 
 int /*<<< orphan*/  MESON_MX_SDIO_SEND_DATA ; 
 int /*<<< orphan*/  MESON_MX_SDIO_SEND_REPEAT_PACKAGE_TIMES_MASK ; 
 int /*<<< orphan*/  MESON_MX_SDIO_SEND_RESP_CRC7_FROM_8 ; 
 int /*<<< orphan*/  MESON_MX_SDIO_SEND_RESP_HAS_DATA ; 
 int /*<<< orphan*/  MESON_MX_SDIO_SEND_RESP_WITHOUT_CRC7 ; 
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 int MMC_DATA_WRITE ; 
 int MMC_RSP_BUSY ; 
 int MMC_RSP_CRC ; 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  meson_mx_mmc_mask_bits (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct meson_mx_mmc_host* mmc_priv (struct mmc_host*) ; 
 int mmc_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_mx_mmc_start_cmd(struct mmc_host *mmc,
				   struct mmc_command *cmd)
{
	struct meson_mx_mmc_host *host = mmc_priv(mmc);
	unsigned int pack_size;
	unsigned long irqflags, timeout;
	u32 mult, send = 0, ext = 0;

	host->cmd = cmd;

	if (cmd->busy_timeout)
		timeout = msecs_to_jiffies(cmd->busy_timeout);
	else
		timeout = msecs_to_jiffies(1000);

	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_R1:
	case MMC_RSP_R1B:
	case MMC_RSP_R3:
		/* 7 (CMD) + 32 (response) + 7 (CRC) -1 */
		send |= FIELD_PREP(MESON_MX_SDIO_SEND_CMD_RESP_BITS_MASK, 45);
		break;
	case MMC_RSP_R2:
		/* 7 (CMD) + 120 (response) + 7 (CRC) -1 */
		send |= FIELD_PREP(MESON_MX_SDIO_SEND_CMD_RESP_BITS_MASK, 133);
		send |= MESON_MX_SDIO_SEND_RESP_CRC7_FROM_8;
		break;
	default:
		break;
	}

	if (!(cmd->flags & MMC_RSP_CRC))
		send |= MESON_MX_SDIO_SEND_RESP_WITHOUT_CRC7;

	if (cmd->flags & MMC_RSP_BUSY)
		send |= MESON_MX_SDIO_SEND_CHECK_DAT0_BUSY;

	if (cmd->data) {
		send |= FIELD_PREP(MESON_MX_SDIO_SEND_REPEAT_PACKAGE_TIMES_MASK,
				   (cmd->data->blocks - 1));

		pack_size = cmd->data->blksz * BITS_PER_BYTE;
		if (mmc->ios.bus_width == MMC_BUS_WIDTH_4)
			pack_size += MESON_MX_SDIO_RESPONSE_CRC16_BITS * 4;
		else
			pack_size += MESON_MX_SDIO_RESPONSE_CRC16_BITS * 1;

		ext |= FIELD_PREP(MESON_MX_SDIO_EXT_DATA_RW_NUMBER_MASK,
				  pack_size);

		if (cmd->data->flags & MMC_DATA_WRITE)
			send |= MESON_MX_SDIO_SEND_DATA;
		else
			send |= MESON_MX_SDIO_SEND_RESP_HAS_DATA;

		cmd->data->bytes_xfered = 0;
	}

	send |= FIELD_PREP(MESON_MX_SDIO_SEND_COMMAND_INDEX_MASK,
			   (0x40 | cmd->opcode));

	spin_lock_irqsave(&host->irq_lock, irqflags);

	mult = readl(host->base + MESON_MX_SDIO_MULT);
	mult &= ~MESON_MX_SDIO_MULT_PORT_SEL_MASK;
	mult |= FIELD_PREP(MESON_MX_SDIO_MULT_PORT_SEL_MASK, host->slot_id);
	mult |= BIT(31);
	writel(mult, host->base + MESON_MX_SDIO_MULT);

	/* enable the CMD done interrupt */
	meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_IRQC,
			       MESON_MX_SDIO_IRQC_ARC_CMD_INT_EN,
			       MESON_MX_SDIO_IRQC_ARC_CMD_INT_EN);

	/* clear pending interrupts */
	meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_IRQS,
			       MESON_MX_SDIO_IRQS_CMD_INT,
			       MESON_MX_SDIO_IRQS_CMD_INT);

	writel(cmd->arg, host->base + MESON_MX_SDIO_ARGU);
	writel(ext, host->base + MESON_MX_SDIO_EXT);
	writel(send, host->base + MESON_MX_SDIO_SEND);

	spin_unlock_irqrestore(&host->irq_lock, irqflags);

	mod_timer(&host->cmd_timeout, jiffies + timeout);
}