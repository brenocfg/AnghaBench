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
struct i40e_nvm_access {scalar_t__ data_size; int /*<<< orphan*/  offset; int /*<<< orphan*/  config; } ;
struct TYPE_2__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_1__ aq; int /*<<< orphan*/  nvm_wb_desc; } ;
struct i40e_asq_cmd_details {int /*<<< orphan*/ * wb_desc; } ;
typedef  scalar_t__ i40e_status ;
typedef  int /*<<< orphan*/  cmd_details ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_DEBUG_NVM ; 
 int I40E_NVM_LCB ; 
 int i40e_aq_rc_to_posix (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_update_nvm (struct i40e_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 int i40e_nvmupd_get_module (int /*<<< orphan*/ ) ; 
 int i40e_nvmupd_get_preservation_flags (int /*<<< orphan*/ ) ; 
 int i40e_nvmupd_get_transaction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i40e_asq_cmd_details*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static i40e_status i40e_nvmupd_nvm_write(struct i40e_hw *hw,
					 struct i40e_nvm_access *cmd,
					 u8 *bytes, int *perrno)
{
	i40e_status status = 0;
	struct i40e_asq_cmd_details cmd_details;
	u8 module, transaction;
	u8 preservation_flags;
	bool last;

	transaction = i40e_nvmupd_get_transaction(cmd->config);
	module = i40e_nvmupd_get_module(cmd->config);
	last = (transaction & I40E_NVM_LCB);
	preservation_flags = i40e_nvmupd_get_preservation_flags(cmd->config);

	memset(&cmd_details, 0, sizeof(cmd_details));
	cmd_details.wb_desc = &hw->nvm_wb_desc;

	status = i40e_aq_update_nvm(hw, module, cmd->offset,
				    (u16)cmd->data_size, bytes, last,
				    preservation_flags, &cmd_details);
	if (status) {
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_nvm_write mod 0x%x off 0x%x len 0x%x\n",
			   module, cmd->offset, cmd->data_size);
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_nvm_write status %d aq %d\n",
			   status, hw->aq.asq_last_status);
		*perrno = i40e_aq_rc_to_posix(status, hw->aq.asq_last_status);
	}

	return status;
}