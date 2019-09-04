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
typedef  int /*<<< orphan*/  u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_suspend_resume_elem {int dummy; } ;
struct ice_aqc_get_cfg_elem {int /*<<< orphan*/  num_elem_resp; int /*<<< orphan*/  num_elem_req; } ;
struct TYPE_2__ {struct ice_aqc_get_cfg_elem get_update_elem; } ;
struct ice_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_adminq_opc { ____Placeholder_ice_adminq_opc } ice_adminq_opc ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_FLAG_RD ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,struct ice_aqc_suspend_resume_elem*,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_suspend_resume_elems(struct ice_hw *hw, u16 elems_req,
			 struct ice_aqc_suspend_resume_elem *buf, u16 buf_size,
			 u16 *elems_ret, struct ice_sq_cd *cd,
			 enum ice_adminq_opc cmd_code)
{
	struct ice_aqc_get_cfg_elem *cmd;
	struct ice_aq_desc desc;
	enum ice_status status;

	cmd = &desc.params.get_update_elem;
	ice_fill_dflt_direct_cmd_desc(&desc, cmd_code);
	cmd->num_elem_req = cpu_to_le16(elems_req);
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	if (!status && elems_ret)
		*elems_ret = le16_to_cpu(cmd->num_elem_resp);
	return status;
}