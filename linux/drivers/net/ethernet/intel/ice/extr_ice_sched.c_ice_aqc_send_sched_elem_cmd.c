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
struct ice_aqc_sched_elem_cmd {int /*<<< orphan*/  num_elem_resp; int /*<<< orphan*/  num_elem_req; } ;
struct TYPE_2__ {struct ice_aqc_sched_elem_cmd sched_elem_cmd; } ;
struct ice_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_adminq_opc { ____Placeholder_ice_adminq_opc } ice_adminq_opc ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_FLAG_RD ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,void*,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_aqc_send_sched_elem_cmd(struct ice_hw *hw, enum ice_adminq_opc cmd_opc,
			    u16 elems_req, void *buf, u16 buf_size,
			    u16 *elems_resp, struct ice_sq_cd *cd)
{
	struct ice_aqc_sched_elem_cmd *cmd;
	struct ice_aq_desc desc;
	enum ice_status status;

	cmd = &desc.params.sched_elem_cmd;
	ice_fill_dflt_direct_cmd_desc(&desc, cmd_opc);
	cmd->num_elem_req = cpu_to_le16(elems_req);
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	if (!status && elems_resp)
		*elems_resp = le16_to_cpu(cmd->num_elem_resp);

	return status;
}