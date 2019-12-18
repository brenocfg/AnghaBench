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
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_lldp_set_mib_change {int /*<<< orphan*/  command; } ;
struct TYPE_2__ {struct ice_aqc_lldp_set_mib_change lldp_set_event; } ;
struct ice_aq_desc {TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_LLDP_MIB_UPDATE_DIS ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_lldp_set_mib_change ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_aq_cfg_lldp_mib_change(struct ice_hw *hw, bool ena_update,
			   struct ice_sq_cd *cd)
{
	struct ice_aqc_lldp_set_mib_change *cmd;
	struct ice_aq_desc desc;

	cmd = &desc.params.lldp_set_event;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_lldp_set_mib_change);

	if (!ena_update)
		cmd->command |= ICE_AQ_LLDP_MIB_UPDATE_DIS;

	return ice_aq_send_cmd(hw, &desc, NULL, 0, cd);
}