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
struct ice_hw {int /*<<< orphan*/  api_patch; int /*<<< orphan*/  api_min_ver; int /*<<< orphan*/  api_maj_ver; int /*<<< orphan*/  api_branch; int /*<<< orphan*/  fw_build; int /*<<< orphan*/  fw_patch; int /*<<< orphan*/  fw_min_ver; int /*<<< orphan*/  fw_maj_ver; int /*<<< orphan*/  fw_branch; } ;
struct ice_aqc_get_ver {int /*<<< orphan*/  api_patch; int /*<<< orphan*/  api_minor; int /*<<< orphan*/  api_major; int /*<<< orphan*/  api_branch; int /*<<< orphan*/  fw_build; int /*<<< orphan*/  fw_patch; int /*<<< orphan*/  fw_minor; int /*<<< orphan*/  fw_major; int /*<<< orphan*/  fw_branch; } ;
struct TYPE_2__ {struct ice_aqc_get_ver get_ver; } ;
struct ice_aq_desc {TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_get_ver ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

enum ice_status ice_aq_get_fw_ver(struct ice_hw *hw, struct ice_sq_cd *cd)
{
	struct ice_aqc_get_ver *resp;
	struct ice_aq_desc desc;
	enum ice_status status;

	resp = &desc.params.get_ver;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_ver);

	status = ice_aq_send_cmd(hw, &desc, NULL, 0, cd);

	if (!status) {
		hw->fw_branch = resp->fw_branch;
		hw->fw_maj_ver = resp->fw_major;
		hw->fw_min_ver = resp->fw_minor;
		hw->fw_patch = resp->fw_patch;
		hw->fw_build = le32_to_cpu(resp->fw_build);
		hw->api_branch = resp->api_branch;
		hw->api_maj_ver = resp->api_major;
		hw->api_min_ver = resp->api_minor;
		hw->api_patch = resp->api_patch;
	}

	return status;
}