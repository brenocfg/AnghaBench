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
typedef  int u32 ;
struct mxcmci_host {int /*<<< orphan*/  mmc; struct mmc_command* cmd; } ;
struct mmc_command {int flags; int* resp; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  MMC_REG_RES_FIFO ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_CRC ; 
 int MMC_RSP_PRESENT ; 
 unsigned int STATUS_RESP_CRC_ERR ; 
 unsigned int STATUS_TIME_OUT_RESP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int mxcmci_readw (struct mxcmci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxcmci_read_response(struct mxcmci_host *host, unsigned int stat)
{
	struct mmc_command *cmd = host->cmd;
	int i;
	u32 a, b, c;

	if (!cmd)
		return;

	if (stat & STATUS_TIME_OUT_RESP) {
		dev_dbg(mmc_dev(host->mmc), "CMD TIMEOUT\n");
		cmd->error = -ETIMEDOUT;
	} else if (stat & STATUS_RESP_CRC_ERR && cmd->flags & MMC_RSP_CRC) {
		dev_dbg(mmc_dev(host->mmc), "cmd crc error\n");
		cmd->error = -EILSEQ;
	}

	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			for (i = 0; i < 4; i++) {
				a = mxcmci_readw(host, MMC_REG_RES_FIFO);
				b = mxcmci_readw(host, MMC_REG_RES_FIFO);
				cmd->resp[i] = a << 16 | b;
			}
		} else {
			a = mxcmci_readw(host, MMC_REG_RES_FIFO);
			b = mxcmci_readw(host, MMC_REG_RES_FIFO);
			c = mxcmci_readw(host, MMC_REG_RES_FIFO);
			cmd->resp[0] = a << 24 | b << 8 | c >> 8;
		}
	}
}