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
typedef  int u32 ;
typedef  int u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_nvm {int offset_high; void* length; void* offset_low; void* module_typeid; int /*<<< orphan*/  cmd_flags; } ;
struct TYPE_2__ {struct ice_aqc_nvm nvm; } ;
struct ice_aq_desc {TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQC_NVM_LAST_CMD ; 
 int ICE_ERR_PARAM ; 
 void* cpu_to_le16 (int) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,void*,int,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_nvm_read ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_aq_read_nvm(struct ice_hw *hw, u16 module_typeid, u32 offset, u16 length,
		void *data, bool last_command, struct ice_sq_cd *cd)
{
	struct ice_aq_desc desc;
	struct ice_aqc_nvm *cmd;

	cmd = &desc.params.nvm;

	/* In offset the highest byte must be zeroed. */
	if (offset & 0xFF000000)
		return ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_read);

	/* If this is the last command in a series, set the proper flag. */
	if (last_command)
		cmd->cmd_flags |= ICE_AQC_NVM_LAST_CMD;
	cmd->module_typeid = cpu_to_le16(module_typeid);
	cmd->offset_low = cpu_to_le16(offset & 0xFFFF);
	cmd->offset_high = (offset >> 16) & 0xFF;
	cmd->length = cpu_to_le16(length);

	return ice_aq_send_cmd(hw, &desc, data, length, cd);
}