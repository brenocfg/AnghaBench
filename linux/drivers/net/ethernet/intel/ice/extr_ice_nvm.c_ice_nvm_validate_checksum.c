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
struct ice_hw {int dummy; } ;
struct ice_aqc_nvm_checksum {int /*<<< orphan*/  checksum; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct ice_aqc_nvm_checksum nvm_checksum; } ;
struct ice_aq_desc {TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 scalar_t__ ICE_AQC_NVM_CHECKSUM_CORRECT ; 
 int /*<<< orphan*/  ICE_AQC_NVM_CHECKSUM_VERIFY ; 
 int ICE_ERR_NVM_CHECKSUM ; 
 int /*<<< orphan*/  ICE_RES_READ ; 
 int ice_acquire_nvm (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_aqc_opc_nvm_checksum ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_release_nvm (struct ice_hw*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

enum ice_status ice_nvm_validate_checksum(struct ice_hw *hw)
{
	struct ice_aqc_nvm_checksum *cmd;
	struct ice_aq_desc desc;
	enum ice_status status;

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	if (status)
		return status;

	cmd = &desc.params.nvm_checksum;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_checksum);
	cmd->flags = ICE_AQC_NVM_CHECKSUM_VERIFY;

	status = ice_aq_send_cmd(hw, &desc, NULL, 0, NULL);
	ice_release_nvm(hw);

	if (!status)
		if (le16_to_cpu(cmd->checksum) != ICE_AQC_NVM_CHECKSUM_CORRECT)
			status = ICE_ERR_NVM_CHECKSUM;

	return status;
}