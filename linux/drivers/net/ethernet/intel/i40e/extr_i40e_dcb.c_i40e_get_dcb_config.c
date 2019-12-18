#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fw_maj_ver; int fw_min_ver; scalar_t__ asq_last_status; } ;
struct TYPE_7__ {int /*<<< orphan*/  tlv_status; void* dcbx_mode; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct i40e_hw {TYPE_2__ aq; int /*<<< orphan*/  remote_dcbx_config; int /*<<< orphan*/  desired_dcbx_config; TYPE_3__ local_dcbx_config; TYPE_1__ mac; } ;
struct i40e_aqc_get_cee_dcb_cfg_v1_resp {int /*<<< orphan*/  tlv_status; } ;
struct i40e_aqc_get_cee_dcb_cfg_resp {int /*<<< orphan*/  tlv_status; } ;
typedef  scalar_t__ i40e_status ;
typedef  int /*<<< orphan*/  cee_v1_cfg ;
typedef  int /*<<< orphan*/  cee_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_AQ_LLDP_BRIDGE_TYPE_NEAREST_BRIDGE ; 
 int /*<<< orphan*/  I40E_AQ_LLDP_MIB_LOCAL ; 
 int /*<<< orphan*/  I40E_AQ_LLDP_MIB_REMOTE ; 
 scalar_t__ I40E_AQ_RC_ENOENT ; 
 void* I40E_DCBX_MODE_CEE ; 
 scalar_t__ I40E_MAC_XL710 ; 
 scalar_t__ i40e_aq_get_cee_dcb_config (struct i40e_hw*,struct i40e_aqc_get_cee_dcb_cfg_v1_resp*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_aq_get_dcb_config (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_cee_to_dcb_config (struct i40e_aqc_get_cee_dcb_cfg_v1_resp*,TYPE_3__*) ; 
 int /*<<< orphan*/  i40e_cee_to_dcb_v1_config (struct i40e_aqc_get_cee_dcb_cfg_v1_resp*,TYPE_3__*) ; 
 scalar_t__ i40e_get_ieee_dcb_config (struct i40e_hw*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

i40e_status i40e_get_dcb_config(struct i40e_hw *hw)
{
	i40e_status ret = 0;
	struct i40e_aqc_get_cee_dcb_cfg_resp cee_cfg;
	struct i40e_aqc_get_cee_dcb_cfg_v1_resp cee_v1_cfg;

	/* If Firmware version < v4.33 on X710/XL710, IEEE only */
	if ((hw->mac.type == I40E_MAC_XL710) &&
	    (((hw->aq.fw_maj_ver == 4) && (hw->aq.fw_min_ver < 33)) ||
	      (hw->aq.fw_maj_ver < 4)))
		return i40e_get_ieee_dcb_config(hw);

	/* If Firmware version == v4.33 on X710/XL710, use old CEE struct */
	if ((hw->mac.type == I40E_MAC_XL710) &&
	    ((hw->aq.fw_maj_ver == 4) && (hw->aq.fw_min_ver == 33))) {
		ret = i40e_aq_get_cee_dcb_config(hw, &cee_v1_cfg,
						 sizeof(cee_v1_cfg), NULL);
		if (!ret) {
			/* CEE mode */
			hw->local_dcbx_config.dcbx_mode = I40E_DCBX_MODE_CEE;
			hw->local_dcbx_config.tlv_status =
					le16_to_cpu(cee_v1_cfg.tlv_status);
			i40e_cee_to_dcb_v1_config(&cee_v1_cfg,
						  &hw->local_dcbx_config);
		}
	} else {
		ret = i40e_aq_get_cee_dcb_config(hw, &cee_cfg,
						 sizeof(cee_cfg), NULL);
		if (!ret) {
			/* CEE mode */
			hw->local_dcbx_config.dcbx_mode = I40E_DCBX_MODE_CEE;
			hw->local_dcbx_config.tlv_status =
					le32_to_cpu(cee_cfg.tlv_status);
			i40e_cee_to_dcb_config(&cee_cfg,
					       &hw->local_dcbx_config);
		}
	}

	/* CEE mode not enabled try querying IEEE data */
	if (hw->aq.asq_last_status == I40E_AQ_RC_ENOENT)
		return i40e_get_ieee_dcb_config(hw);

	if (ret)
		goto out;

	/* Get CEE DCB Desired Config */
	ret = i40e_aq_get_dcb_config(hw, I40E_AQ_LLDP_MIB_LOCAL, 0,
				     &hw->desired_dcbx_config);
	if (ret)
		goto out;

	/* Get Remote DCB Config */
	ret = i40e_aq_get_dcb_config(hw, I40E_AQ_LLDP_MIB_REMOTE,
				     I40E_AQ_LLDP_BRIDGE_TYPE_NEAREST_BRIDGE,
				     &hw->remote_dcbx_config);
	/* Don't treat ENOENT as an error for Remote MIBs */
	if (hw->aq.asq_last_status == I40E_AQ_RC_ENOENT)
		ret = 0;

out:
	return ret;
}