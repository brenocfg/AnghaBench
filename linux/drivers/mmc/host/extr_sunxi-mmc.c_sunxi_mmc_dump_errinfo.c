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
struct sunxi_mmc_host {int int_sum; TYPE_2__* mmc; TYPE_1__* mrq; } ;
struct mmc_data {int flags; } ;
struct mmc_command {scalar_t__ opcode; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct TYPE_3__ {struct mmc_data* data; struct mmc_command* cmd; } ;

/* Variables and functions */
 int MMC_DATA_WRITE ; 
 int SDXC_DATA_CRC_ERROR ; 
 int SDXC_DATA_TIMEOUT ; 
 int SDXC_END_BIT_ERROR ; 
 int SDXC_FIFO_RUN_ERROR ; 
 int SDXC_HARD_WARE_LOCKED ; 
 int SDXC_INTERRUPT_ERROR_BIT ; 
 int SDXC_RESP_CRC_ERROR ; 
 int SDXC_RESP_ERROR ; 
 int SDXC_RESP_TIMEOUT ; 
 int SDXC_START_BIT_ERROR ; 
 scalar_t__ SD_IO_RW_DIRECT ; 
 scalar_t__ SD_IO_SEND_OP_COND ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_2__*) ; 

__attribute__((used)) static void sunxi_mmc_dump_errinfo(struct sunxi_mmc_host *host)
{
	struct mmc_command *cmd = host->mrq->cmd;
	struct mmc_data *data = host->mrq->data;

	/* For some cmds timeout is normal with sd/mmc cards */
	if ((host->int_sum & SDXC_INTERRUPT_ERROR_BIT) ==
		SDXC_RESP_TIMEOUT && (cmd->opcode == SD_IO_SEND_OP_COND ||
				      cmd->opcode == SD_IO_RW_DIRECT))
		return;

	dev_dbg(mmc_dev(host->mmc),
		"smc %d err, cmd %d,%s%s%s%s%s%s%s%s%s%s !!\n",
		host->mmc->index, cmd->opcode,
		data ? (data->flags & MMC_DATA_WRITE ? " WR" : " RD") : "",
		host->int_sum & SDXC_RESP_ERROR     ? " RE"     : "",
		host->int_sum & SDXC_RESP_CRC_ERROR  ? " RCE"    : "",
		host->int_sum & SDXC_DATA_CRC_ERROR  ? " DCE"    : "",
		host->int_sum & SDXC_RESP_TIMEOUT ? " RTO"    : "",
		host->int_sum & SDXC_DATA_TIMEOUT ? " DTO"    : "",
		host->int_sum & SDXC_FIFO_RUN_ERROR  ? " FE"     : "",
		host->int_sum & SDXC_HARD_WARE_LOCKED ? " HL"     : "",
		host->int_sum & SDXC_START_BIT_ERROR ? " SBE"    : "",
		host->int_sum & SDXC_END_BIT_ERROR   ? " EBE"    : ""
		);
}