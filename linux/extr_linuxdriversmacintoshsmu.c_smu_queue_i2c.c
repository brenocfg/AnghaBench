#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int* reply_buf; int reply_len; int status; int data_len; int /*<<< orphan*/  link; int /*<<< orphan*/ * data_buf; struct smu_i2c_cmd* misc; int /*<<< orphan*/  done; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {int caddr; int devaddr; int type; int sublen; int datalen; int* data; int /*<<< orphan*/ * subaddr; int /*<<< orphan*/  bus; } ;
struct smu_i2c_cmd {int* pdata; int retries; int status; int read; int /*<<< orphan*/  link; TYPE_2__ scmd; TYPE_1__ info; scalar_t__ stage; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cmd_i2c_list; int /*<<< orphan*/ * cmd_cur; int /*<<< orphan*/  cmd_list; struct smu_i2c_cmd* cmd_i2c_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  SMU_CMD_I2C_COMMAND ; 
 int SMU_I2C_READ_MAX ; 
#define  SMU_I2C_TRANSFER_COMBINED 130 
#define  SMU_I2C_TRANSFER_SIMPLE 129 
#define  SMU_I2C_TRANSFER_STDSUB 128 
 int SMU_I2C_WRITE_MAX ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 TYPE_3__* smu ; 
 int /*<<< orphan*/  smu_i2c_low_completion ; 
 int /*<<< orphan*/  smu_start_cmd () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int smu_queue_i2c(struct smu_i2c_cmd *cmd)
{
	unsigned long flags;

	if (smu == NULL)
		return -ENODEV;

	/* Fill most fields of scmd */
	cmd->scmd.cmd = SMU_CMD_I2C_COMMAND;
	cmd->scmd.done = smu_i2c_low_completion;
	cmd->scmd.misc = cmd;
	cmd->scmd.reply_buf = cmd->pdata;
	cmd->scmd.reply_len = sizeof(cmd->pdata);
	cmd->scmd.data_buf = (u8 *)(char *)&cmd->info;
	cmd->scmd.status = 1;
	cmd->stage = 0;
	cmd->pdata[0] = 0xff;
	cmd->retries = 20;
	cmd->status = 1;

	/* Check transfer type, sanitize some "info" fields
	 * based on transfer type and do more checking
	 */
	cmd->info.caddr = cmd->info.devaddr;
	cmd->read = cmd->info.devaddr & 0x01;
	switch(cmd->info.type) {
	case SMU_I2C_TRANSFER_SIMPLE:
		memset(&cmd->info.sublen, 0, 4);
		break;
	case SMU_I2C_TRANSFER_COMBINED:
		cmd->info.devaddr &= 0xfe;
	case SMU_I2C_TRANSFER_STDSUB:
		if (cmd->info.sublen > 3)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	/* Finish setting up command based on transfer direction
	 */
	if (cmd->read) {
		if (cmd->info.datalen > SMU_I2C_READ_MAX)
			return -EINVAL;
		memset(cmd->info.data, 0xff, cmd->info.datalen);
		cmd->scmd.data_len = 9;
	} else {
		if (cmd->info.datalen > SMU_I2C_WRITE_MAX)
			return -EINVAL;
		cmd->scmd.data_len = 9 + cmd->info.datalen;
	}

	DPRINTK("SMU: i2c enqueuing command\n");
	DPRINTK("SMU:   %s, len=%d bus=%x addr=%x sub0=%x type=%x\n",
		cmd->read ? "read" : "write", cmd->info.datalen,
		cmd->info.bus, cmd->info.caddr,
		cmd->info.subaddr[0], cmd->info.type);


	/* Enqueue command in i2c list, and if empty, enqueue also in
	 * main command list
	 */
	spin_lock_irqsave(&smu->lock, flags);
	if (smu->cmd_i2c_cur == NULL) {
		smu->cmd_i2c_cur = cmd;
		list_add_tail(&cmd->scmd.link, &smu->cmd_list);
		if (smu->cmd_cur == NULL)
			smu_start_cmd();
	} else
		list_add_tail(&cmd->link, &smu->cmd_i2c_list);
	spin_unlock_irqrestore(&smu->lock, flags);

	return 0;
}