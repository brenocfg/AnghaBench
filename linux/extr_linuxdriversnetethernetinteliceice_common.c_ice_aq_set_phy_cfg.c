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
typedef  int /*<<< orphan*/  u8 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_set_phy_cfg_data {int dummy; } ;
struct ice_aqc_set_phy_cfg {int /*<<< orphan*/  lport_num; } ;
struct TYPE_2__ {struct ice_aqc_set_phy_cfg set_phy; } ;
struct ice_aq_desc {TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_PARAM ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,struct ice_aqc_set_phy_cfg_data*,int,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_set_phy_cfg ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_aq_set_phy_cfg(struct ice_hw *hw, u8 lport,
		   struct ice_aqc_set_phy_cfg_data *cfg, struct ice_sq_cd *cd)
{
	struct ice_aqc_set_phy_cfg *cmd;
	struct ice_aq_desc desc;

	if (!cfg)
		return ICE_ERR_PARAM;

	cmd = &desc.params.set_phy;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_set_phy_cfg);
	cmd->lport_num = lport;

	return ice_aq_send_cmd(hw, &desc, cfg, sizeof(*cfg), cd);
}