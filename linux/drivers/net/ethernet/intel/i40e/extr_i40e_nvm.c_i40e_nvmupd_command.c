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
typedef  int /*<<< orphan*/  u16 ;
struct i40e_nvm_access {int offset; int data_size; int /*<<< orphan*/  config; int /*<<< orphan*/  command; } ;
struct TYPE_2__ {int /*<<< orphan*/  arq_mutex; } ;
struct i40e_hw {int nvmupd_state; TYPE_1__ aq; int /*<<< orphan*/  nvm_wait_opcode; int /*<<< orphan*/  nvm_release_on_done; } ;
typedef  int /*<<< orphan*/  i40e_status ;
typedef  enum i40e_nvmupd_cmd { ____Placeholder_i40e_nvmupd_cmd } i40e_nvmupd_cmd ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int ESRCH ; 
 int /*<<< orphan*/  I40E_DEBUG_NVM ; 
 int /*<<< orphan*/  I40E_ERR_BUF_TOO_SHORT ; 
 int /*<<< orphan*/  I40E_ERR_NOT_READY ; 
 int /*<<< orphan*/  I40E_NOT_SUPPORTED ; 
 int I40E_NVMUPD_INVALID ; 
 int I40E_NVMUPD_STATE_ERROR ; 
#define  I40E_NVMUPD_STATE_INIT 132 
#define  I40E_NVMUPD_STATE_INIT_WAIT 131 
#define  I40E_NVMUPD_STATE_READING 130 
#define  I40E_NVMUPD_STATE_WRITE_WAIT 129 
#define  I40E_NVMUPD_STATE_WRITING 128 
 int I40E_NVMUPD_STATUS ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * i40e_nvm_update_state_str ; 
 int /*<<< orphan*/  i40e_nvmupd_clear_wait_state (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_nvmupd_state_init (struct i40e_hw*,struct i40e_nvm_access*,int*,int*) ; 
 int /*<<< orphan*/  i40e_nvmupd_state_reading (struct i40e_hw*,struct i40e_nvm_access*,int*,int*) ; 
 int /*<<< orphan*/  i40e_nvmupd_state_writing (struct i40e_hw*,struct i40e_nvm_access*,int*,int*) ; 
 int i40e_nvmupd_validate_command (struct i40e_hw*,struct i40e_nvm_access*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

i40e_status i40e_nvmupd_command(struct i40e_hw *hw,
				struct i40e_nvm_access *cmd,
				u8 *bytes, int *perrno)
{
	i40e_status status;
	enum i40e_nvmupd_cmd upd_cmd;

	/* assume success */
	*perrno = 0;

	/* early check for status command and debug msgs */
	upd_cmd = i40e_nvmupd_validate_command(hw, cmd, perrno);

	i40e_debug(hw, I40E_DEBUG_NVM, "%s state %d nvm_release_on_hold %d opc 0x%04x cmd 0x%08x config 0x%08x offset 0x%08x data_size 0x%08x\n",
		   i40e_nvm_update_state_str[upd_cmd],
		   hw->nvmupd_state,
		   hw->nvm_release_on_done, hw->nvm_wait_opcode,
		   cmd->command, cmd->config, cmd->offset, cmd->data_size);

	if (upd_cmd == I40E_NVMUPD_INVALID) {
		*perrno = -EFAULT;
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_validate_command returns %d errno %d\n",
			   upd_cmd, *perrno);
	}

	/* a status request returns immediately rather than
	 * going into the state machine
	 */
	if (upd_cmd == I40E_NVMUPD_STATUS) {
		if (!cmd->data_size) {
			*perrno = -EFAULT;
			return I40E_ERR_BUF_TOO_SHORT;
		}

		bytes[0] = hw->nvmupd_state;

		if (cmd->data_size >= 4) {
			bytes[1] = 0;
			*((u16 *)&bytes[2]) = hw->nvm_wait_opcode;
		}

		/* Clear error status on read */
		if (hw->nvmupd_state == I40E_NVMUPD_STATE_ERROR)
			hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;

		return 0;
	}

	/* Clear status even it is not read and log */
	if (hw->nvmupd_state == I40E_NVMUPD_STATE_ERROR) {
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "Clearing I40E_NVMUPD_STATE_ERROR state without reading\n");
		hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;
	}

	/* Acquire lock to prevent race condition where adminq_task
	 * can execute after i40e_nvmupd_nvm_read/write but before state
	 * variables (nvm_wait_opcode, nvm_release_on_done) are updated.
	 *
	 * During NVMUpdate, it is observed that lock could be held for
	 * ~5ms for most commands. However lock is held for ~60ms for
	 * NVMUPD_CSUM_LCB command.
	 */
	mutex_lock(&hw->aq.arq_mutex);
	switch (hw->nvmupd_state) {
	case I40E_NVMUPD_STATE_INIT:
		status = i40e_nvmupd_state_init(hw, cmd, bytes, perrno);
		break;

	case I40E_NVMUPD_STATE_READING:
		status = i40e_nvmupd_state_reading(hw, cmd, bytes, perrno);
		break;

	case I40E_NVMUPD_STATE_WRITING:
		status = i40e_nvmupd_state_writing(hw, cmd, bytes, perrno);
		break;

	case I40E_NVMUPD_STATE_INIT_WAIT:
	case I40E_NVMUPD_STATE_WRITE_WAIT:
		/* if we need to stop waiting for an event, clear
		 * the wait info and return before doing anything else
		 */
		if (cmd->offset == 0xffff) {
			i40e_nvmupd_clear_wait_state(hw);
			status = 0;
			break;
		}

		status = I40E_ERR_NOT_READY;
		*perrno = -EBUSY;
		break;

	default:
		/* invalid state, should never happen */
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVMUPD: no such state %d\n", hw->nvmupd_state);
		status = I40E_NOT_SUPPORTED;
		*perrno = -ESRCH;
		break;
	}

	mutex_unlock(&hw->aq.arq_mutex);
	return status;
}