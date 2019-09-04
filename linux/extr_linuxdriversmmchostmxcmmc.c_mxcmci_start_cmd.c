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
typedef  int /*<<< orphan*/  u32 ;
struct mxcmci_host {scalar_t__ dma_dir; int /*<<< orphan*/  lock; scalar_t__ use_sdio; TYPE_1__* desc; int /*<<< orphan*/  mmc; struct mmc_command* cmd; int /*<<< orphan*/  default_irq_mask; } ;
struct mmc_command {int error; unsigned int opcode; int /*<<< orphan*/  arg; } ;
struct TYPE_2__ {struct mxcmci_host* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 unsigned int CMD_DAT_CONT_RESPONSE_136BIT ; 
 unsigned int CMD_DAT_CONT_RESPONSE_48BIT ; 
 unsigned int CMD_DAT_CONT_RESPONSE_48BIT_CRC ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 int EINVAL ; 
 int /*<<< orphan*/  INT_END_CMD_RES_EN ; 
 int /*<<< orphan*/  INT_SDIO_IRQ_EN ; 
 int /*<<< orphan*/  INT_WRITE_OP_DONE_EN ; 
 int /*<<< orphan*/  MMC_REG_ARG ; 
 int /*<<< orphan*/  MMC_REG_CMD ; 
 int /*<<< orphan*/  MMC_REG_CMD_DAT_CONT ; 
 int /*<<< orphan*/  MMC_REG_INT_CNTR ; 
#define  MMC_RSP_NONE 132 
#define  MMC_RSP_R1 131 
#define  MMC_RSP_R1B 130 
#define  MMC_RSP_R2 129 
#define  MMC_RSP_R3 128 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int mmc_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  mxcmci_dma_callback ; 
 scalar_t__ mxcmci_use_dma (struct mxcmci_host*) ; 
 int /*<<< orphan*/  mxcmci_writel (struct mxcmci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxcmci_writew (struct mxcmci_host*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mxcmci_start_cmd(struct mxcmci_host *host, struct mmc_command *cmd,
		unsigned int cmdat)
{
	u32 int_cntr = host->default_irq_mask;
	unsigned long flags;

	WARN_ON(host->cmd != NULL);
	host->cmd = cmd;

	switch (mmc_resp_type(cmd)) {
	case MMC_RSP_R1: /* short CRC, OPCODE */
	case MMC_RSP_R1B:/* short CRC, OPCODE, BUSY */
		cmdat |= CMD_DAT_CONT_RESPONSE_48BIT_CRC;
		break;
	case MMC_RSP_R2: /* long 136 bit + CRC */
		cmdat |= CMD_DAT_CONT_RESPONSE_136BIT;
		break;
	case MMC_RSP_R3: /* short */
		cmdat |= CMD_DAT_CONT_RESPONSE_48BIT;
		break;
	case MMC_RSP_NONE:
		break;
	default:
		dev_err(mmc_dev(host->mmc), "unhandled response type 0x%x\n",
				mmc_resp_type(cmd));
		cmd->error = -EINVAL;
		return -EINVAL;
	}

	int_cntr = INT_END_CMD_RES_EN;

	if (mxcmci_use_dma(host)) {
		if (host->dma_dir == DMA_FROM_DEVICE) {
			host->desc->callback = mxcmci_dma_callback;
			host->desc->callback_param = host;
		} else {
			int_cntr |= INT_WRITE_OP_DONE_EN;
		}
	}

	spin_lock_irqsave(&host->lock, flags);
	if (host->use_sdio)
		int_cntr |= INT_SDIO_IRQ_EN;
	mxcmci_writel(host, int_cntr, MMC_REG_INT_CNTR);
	spin_unlock_irqrestore(&host->lock, flags);

	mxcmci_writew(host, cmd->opcode, MMC_REG_CMD);
	mxcmci_writel(host, cmd->arg, MMC_REG_ARG);
	mxcmci_writew(host, cmdat, MMC_REG_CMD_DAT_CONT);

	return 0;
}