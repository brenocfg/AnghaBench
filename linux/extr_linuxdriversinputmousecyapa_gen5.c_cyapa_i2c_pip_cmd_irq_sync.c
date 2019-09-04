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
typedef  int u8 ;
struct cyapa_pip_cmd_states {int* resp_data; int* resp_len; int in_progress_cmd; int is_irq_mode; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/ * resp_sort_func; } ;
struct TYPE_2__ {struct cyapa_pip_cmd_states pip; } ;
struct cyapa {TYPE_1__ cmd_states; } ;
typedef  int /*<<< orphan*/ * cb_sort ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int PIP_APP_CMD_REPORT_ID ; 
 int PIP_BL_CMD_REPORT_ID ; 
 int PIP_INVALID_CMD ; 
 int PIP_MIN_APP_CMD_LENGTH ; 
 int PIP_MIN_BL_CMD_LENGTH ; 
 int cyapa_do_i2c_pip_cmd_irq_sync (struct cyapa*,int*,int,unsigned long) ; 
 int cyapa_do_i2c_pip_cmd_polling (struct cyapa*,int*,int,int*,int*,unsigned long,int /*<<< orphan*/ *) ; 
 int cyapa_empty_pip_output_data (struct cyapa*,int*,int*,int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cyapa_i2c_pip_cmd_irq_sync(
		struct cyapa *cyapa,
		u8 *cmd, int cmd_len,
		u8 *resp_data, int *resp_len,
		unsigned long timeout,
		cb_sort func,
		bool irq_mode)
{
	struct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int error;

	if (!cmd || !cmd_len)
		return -EINVAL;

	/* Commands must be serialized. */
	error = mutex_lock_interruptible(&pip->cmd_lock);
	if (error)
		return error;

	pip->resp_sort_func = func;
	pip->resp_data = resp_data;
	pip->resp_len = resp_len;

	if (cmd_len >= PIP_MIN_APP_CMD_LENGTH &&
			cmd[4] == PIP_APP_CMD_REPORT_ID) {
		/* Application command */
		pip->in_progress_cmd = cmd[6] & 0x7f;
	} else if (cmd_len >= PIP_MIN_BL_CMD_LENGTH &&
			cmd[4] == PIP_BL_CMD_REPORT_ID) {
		/* Bootloader command */
		pip->in_progress_cmd = cmd[7];
	}

	/* Send command data, wait and read output response data's length. */
	if (irq_mode) {
		pip->is_irq_mode = true;
		error = cyapa_do_i2c_pip_cmd_irq_sync(cyapa, cmd, cmd_len,
							timeout);
		if (error == -ETIMEDOUT && resp_data &&
				resp_len && *resp_len != 0 && func) {
			/*
			 * For some old version, there was no interrupt for
			 * the command response data, so need to poll here
			 * to try to get the response data.
			 */
			error = cyapa_empty_pip_output_data(cyapa,
					resp_data, resp_len, func);
			if (error || *resp_len == 0)
				error = error ? error : -ETIMEDOUT;
		}
	} else {
		pip->is_irq_mode = false;
		error = cyapa_do_i2c_pip_cmd_polling(cyapa, cmd, cmd_len,
				resp_data, resp_len, timeout, func);
	}

	pip->resp_sort_func = NULL;
	pip->resp_data = NULL;
	pip->resp_len = NULL;
	pip->in_progress_cmd = PIP_INVALID_CMD;

	mutex_unlock(&pip->cmd_lock);
	return error;
}