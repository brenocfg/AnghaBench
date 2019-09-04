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
typedef  int u64 ;
struct mmc_request {struct mmc_command* cmd; } ;
struct mmc_host {int dummy; } ;
struct mmc_command {int opcode; int arg; TYPE_1__* data; } ;
struct cvm_mmc_slot {int /*<<< orphan*/  bus_id; struct cvm_mmc_host* host; } ;
struct cvm_mmc_host {int dma_active; scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* int_enable ) (struct cvm_mmc_host*,int) ;struct mmc_request* current_req; int /*<<< orphan*/  (* acquire_bus ) (struct cvm_mmc_host*) ;} ;
struct cvm_mmc_cr_mods {int ctype_xor; int rtype_xor; } ;
struct TYPE_2__ {int flags; int blocks; int blksz; scalar_t__ timeout_ns; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MIO_EMM_CMD (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  MIO_EMM_CMD_ARG ; 
 int /*<<< orphan*/  MIO_EMM_CMD_CTYPE_XOR ; 
 int /*<<< orphan*/  MIO_EMM_CMD_IDX ; 
 int /*<<< orphan*/  MIO_EMM_CMD_OFFSET ; 
 int /*<<< orphan*/  MIO_EMM_CMD_RTYPE_XOR ; 
 int /*<<< orphan*/  MIO_EMM_CMD_VAL ; 
 int MIO_EMM_INT_CMD_DONE ; 
 int MIO_EMM_INT_CMD_ERR ; 
 scalar_t__ MIO_EMM_RSP_STS (struct cvm_mmc_host*) ; 
 int MIO_EMM_RSP_STS_CMD_VAL ; 
 int MIO_EMM_RSP_STS_DMA_PEND ; 
 int MIO_EMM_RSP_STS_DMA_VAL ; 
 int MIO_EMM_RSP_STS_SWITCH_VAL ; 
 scalar_t__ MIO_EMM_STS_MASK (struct cvm_mmc_host*) ; 
 scalar_t__ MMC_CMD_ADTC ; 
 int MMC_DATA_READ ; 
 int MMC_READ_MULTIPLE_BLOCK ; 
 int MMC_WRITE_MULTIPLE_BLOCK ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_request*) ; 
 void cvm_mmc_dma_request (struct mmc_host*,struct mmc_request*) ; 
 struct cvm_mmc_cr_mods cvm_mmc_get_cr_mods (struct mmc_command*) ; 
 int /*<<< orphan*/  cvm_mmc_switch_to (struct cvm_mmc_slot*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  do_read_request (struct cvm_mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  do_write_request (struct cvm_mmc_host*,struct mmc_request*) ; 
 scalar_t__ mmc_cmd_type (struct mmc_command*) ; 
 struct cvm_mmc_slot* mmc_priv (struct mmc_host*) ; 
 int readq (scalar_t__) ; 
 int /*<<< orphan*/  set_bus_id (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_wdog (struct cvm_mmc_slot*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  stub2 (struct cvm_mmc_host*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static void cvm_mmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct cvm_mmc_slot *slot = mmc_priv(mmc);
	struct cvm_mmc_host *host = slot->host;
	struct mmc_command *cmd = mrq->cmd;
	struct cvm_mmc_cr_mods mods;
	u64 emm_cmd, rsp_sts;
	int retries = 100;

	/*
	 * Note about locking:
	 * All MMC devices share the same bus and controller. Allow only a
	 * single user of the bootbus/MMC bus at a time. The lock is acquired
	 * on all entry points from the MMC layer.
	 *
	 * For requests the lock is only released after the completion
	 * interrupt!
	 */
	host->acquire_bus(host);

	if (cmd->opcode == MMC_READ_MULTIPLE_BLOCK ||
	    cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK)
		return cvm_mmc_dma_request(mmc, mrq);

	cvm_mmc_switch_to(slot);

	mods = cvm_mmc_get_cr_mods(cmd);

	WARN_ON(host->current_req);
	host->current_req = mrq;

	if (cmd->data) {
		if (cmd->data->flags & MMC_DATA_READ)
			do_read_request(host, mrq);
		else
			do_write_request(host, mrq);

		if (cmd->data->timeout_ns)
			set_wdog(slot, cmd->data->timeout_ns);
	} else
		set_wdog(slot, 0);

	host->dma_active = false;
	host->int_enable(host, MIO_EMM_INT_CMD_DONE | MIO_EMM_INT_CMD_ERR);

	emm_cmd = FIELD_PREP(MIO_EMM_CMD_VAL, 1) |
		  FIELD_PREP(MIO_EMM_CMD_CTYPE_XOR, mods.ctype_xor) |
		  FIELD_PREP(MIO_EMM_CMD_RTYPE_XOR, mods.rtype_xor) |
		  FIELD_PREP(MIO_EMM_CMD_IDX, cmd->opcode) |
		  FIELD_PREP(MIO_EMM_CMD_ARG, cmd->arg);
	set_bus_id(&emm_cmd, slot->bus_id);
	if (cmd->data && mmc_cmd_type(cmd) == MMC_CMD_ADTC)
		emm_cmd |= FIELD_PREP(MIO_EMM_CMD_OFFSET,
				64 - ((cmd->data->blocks * cmd->data->blksz) / 8));

	writeq(0, host->base + MIO_EMM_STS_MASK(host));

retry:
	rsp_sts = readq(host->base + MIO_EMM_RSP_STS(host));
	if (rsp_sts & MIO_EMM_RSP_STS_DMA_VAL ||
	    rsp_sts & MIO_EMM_RSP_STS_CMD_VAL ||
	    rsp_sts & MIO_EMM_RSP_STS_SWITCH_VAL ||
	    rsp_sts & MIO_EMM_RSP_STS_DMA_PEND) {
		udelay(10);
		if (--retries)
			goto retry;
	}
	if (!retries)
		dev_err(host->dev, "Bad status: %llx before command write\n", rsp_sts);
	writeq(emm_cmd, host->base + MIO_EMM_CMD(host));
}