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
struct i40e_nvm_access {int dummy; } ;
struct i40e_hw {int /*<<< orphan*/  nvmupd_state; } ;
typedef  int /*<<< orphan*/  i40e_status ;
typedef  enum i40e_nvmupd_cmd { ____Placeholder_i40e_nvmupd_cmd } i40e_nvmupd_cmd ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  I40E_DEBUG_NVM ; 
 int /*<<< orphan*/  I40E_NOT_SUPPORTED ; 
#define  I40E_NVMUPD_READ_CON 130 
#define  I40E_NVMUPD_READ_LCB 129 
#define  I40E_NVMUPD_READ_SA 128 
 int /*<<< orphan*/  I40E_NVMUPD_STATE_INIT ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * i40e_nvm_update_state_str ; 
 int /*<<< orphan*/  i40e_nvmupd_nvm_read (struct i40e_hw*,struct i40e_nvm_access*,int /*<<< orphan*/ *,int*) ; 
 int i40e_nvmupd_validate_command (struct i40e_hw*,struct i40e_nvm_access*,int*) ; 
 int /*<<< orphan*/  i40e_release_nvm (struct i40e_hw*) ; 

__attribute__((used)) static i40e_status i40e_nvmupd_state_reading(struct i40e_hw *hw,
					     struct i40e_nvm_access *cmd,
					     u8 *bytes, int *perrno)
{
	i40e_status status = 0;
	enum i40e_nvmupd_cmd upd_cmd;

	upd_cmd = i40e_nvmupd_validate_command(hw, cmd, perrno);

	switch (upd_cmd) {
	case I40E_NVMUPD_READ_SA:
	case I40E_NVMUPD_READ_CON:
		status = i40e_nvmupd_nvm_read(hw, cmd, bytes, perrno);
		break;

	case I40E_NVMUPD_READ_LCB:
		status = i40e_nvmupd_nvm_read(hw, cmd, bytes, perrno);
		i40e_release_nvm(hw);
		hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;
		break;

	default:
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVMUPD: bad cmd %s in reading state.\n",
			   i40e_nvm_update_state_str[upd_cmd]);
		status = I40E_NOT_SUPPORTED;
		*perrno = -ESRCH;
		break;
	}
	return status;
}