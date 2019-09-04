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
struct timer_list {int dummy; } ;
struct TYPE_3__ {int reply_len; } ;
struct smu_i2c_cmd {int* pdata; TYPE_1__ scmd; } ;
struct TYPE_4__ {struct smu_i2c_cmd* cmd_i2c_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_2__* smu ; 
 int /*<<< orphan*/  smu_queue_cmd (TYPE_1__*) ; 

__attribute__((used)) static void smu_i2c_retry(struct timer_list *unused)
{
	struct smu_i2c_cmd	*cmd = smu->cmd_i2c_cur;

	DPRINTK("SMU: i2c failure, requeuing...\n");

	/* requeue command simply by resetting reply_len */
	cmd->pdata[0] = 0xff;
	cmd->scmd.reply_len = sizeof(cmd->pdata);
	smu_queue_cmd(&cmd->scmd);
}