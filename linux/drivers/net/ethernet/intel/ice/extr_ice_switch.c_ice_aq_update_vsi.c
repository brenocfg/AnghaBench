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
struct ice_vsi_ctx {int vsi_num; void* vsis_unallocated; void* vsis_allocd; int /*<<< orphan*/  info; } ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_add_update_free_vsi_resp {int /*<<< orphan*/  vsi_free; int /*<<< orphan*/  vsi_used; } ;
struct ice_aqc_add_get_update_free_vsi {int /*<<< orphan*/  vsi_num; } ;
struct TYPE_2__ {struct ice_aqc_add_update_free_vsi_resp add_update_free_vsi_res; struct ice_aqc_add_get_update_free_vsi vsi_cmd; } ;
struct ice_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_AQ_FLAG_RD ; 
 int ICE_AQ_VSI_IS_VALID ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,int /*<<< orphan*/ *,int,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_update_vsi ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_aq_update_vsi(struct ice_hw *hw, struct ice_vsi_ctx *vsi_ctx,
		  struct ice_sq_cd *cd)
{
	struct ice_aqc_add_update_free_vsi_resp *resp;
	struct ice_aqc_add_get_update_free_vsi *cmd;
	struct ice_aq_desc desc;
	enum ice_status status;

	cmd = &desc.params.vsi_cmd;
	resp = &desc.params.add_update_free_vsi_res;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_update_vsi);

	cmd->vsi_num = cpu_to_le16(vsi_ctx->vsi_num | ICE_AQ_VSI_IS_VALID);

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	status = ice_aq_send_cmd(hw, &desc, &vsi_ctx->info,
				 sizeof(vsi_ctx->info), cd);

	if (!status) {
		vsi_ctx->vsis_allocd = le16_to_cpu(resp->vsi_used);
		vsi_ctx->vsis_unallocated = le16_to_cpu(resp->vsi_free);
	}

	return status;
}