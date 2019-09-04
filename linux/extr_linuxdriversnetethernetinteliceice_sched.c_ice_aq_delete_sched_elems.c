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
struct ice_aqc_delete_elem {int dummy; } ;
struct ice_aqc_add_move_delete_elem {int /*<<< orphan*/  num_grps_updated; int /*<<< orphan*/  num_grps_req; } ;
struct TYPE_2__ {struct ice_aqc_add_move_delete_elem add_move_delete_elem; } ;
struct ice_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_FLAG_RD ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,struct ice_aqc_delete_elem*,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_delete_sched_elems ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_aq_delete_sched_elems(struct ice_hw *hw, u16 grps_req,
			  struct ice_aqc_delete_elem *buf, u16 buf_size,
			  u16 *grps_del, struct ice_sq_cd *cd)
{
	struct ice_aqc_add_move_delete_elem *cmd;
	struct ice_aq_desc desc;
	enum ice_status status;

	cmd = &desc.params.add_move_delete_elem;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_delete_sched_elems);
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	cmd->num_grps_req = cpu_to_le16(grps_req);

	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	if (!status && grps_del)
		*grps_del = le16_to_cpu(cmd->num_grps_updated);

	return status;
}