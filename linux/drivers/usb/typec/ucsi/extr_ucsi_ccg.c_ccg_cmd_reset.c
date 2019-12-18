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
typedef  int /*<<< orphan*/  u8 ;
struct ucsi_ccg {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct ccg_cmd {int len; int delay; int /*<<< orphan*/  reg; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCGX_RAB_RESET_REQ ; 
 int /*<<< orphan*/  CMD_RESET_DEV ; 
 int RESET_COMPLETE ; 
 int /*<<< orphan*/  RESET_PENDING ; 
 int /*<<< orphan*/  RESET_SIG ; 
 int ccg_send_command (struct ucsi_ccg*,struct ccg_cmd*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccg_cmd_reset(struct ucsi_ccg *uc)
{
	struct ccg_cmd cmd;
	u8 *p;
	int ret;

	p = (u8 *)&cmd.data;
	cmd.reg = CCGX_RAB_RESET_REQ;
	p[0] = RESET_SIG;
	p[1] = CMD_RESET_DEV;
	cmd.len = 2;
	cmd.delay = 5000;

	mutex_lock(&uc->lock);

	set_bit(RESET_PENDING, &uc->flags);

	ret = ccg_send_command(uc, &cmd);
	if (ret != RESET_COMPLETE)
		goto err_clear_flag;

	ret = 0;

err_clear_flag:
	clear_bit(RESET_PENDING, &uc->flags);

	mutex_unlock(&uc->lock);

	return ret;
}