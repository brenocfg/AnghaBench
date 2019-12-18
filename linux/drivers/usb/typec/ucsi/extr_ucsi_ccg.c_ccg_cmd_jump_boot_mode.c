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
struct ucsi_ccg {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct ccg_cmd {int len; int delay; int /*<<< orphan*/  data; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCGX_RAB_JUMP_TO_BOOT ; 
 int RESET_COMPLETE ; 
 int /*<<< orphan*/  RESET_PENDING ; 
 int /*<<< orphan*/  TO_ALT_FW ; 
 int /*<<< orphan*/  TO_BOOT ; 
 int ccg_send_command (struct ucsi_ccg*,struct ccg_cmd*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccg_cmd_jump_boot_mode(struct ucsi_ccg *uc, int bl_mode)
{
	struct ccg_cmd cmd;
	int ret;

	cmd.reg = CCGX_RAB_JUMP_TO_BOOT;

	if (bl_mode)
		cmd.data = TO_BOOT;
	else
		cmd.data = TO_ALT_FW;

	cmd.len = 1;
	cmd.delay = 100;

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