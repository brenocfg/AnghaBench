#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ice_sq_cd {int dummy; } ;
struct TYPE_4__ {scalar_t__ sq_last_status; } ;
struct ice_hw {TYPE_2__ adminq; } ;
struct ice_aqc_req_res {void* timeout; int /*<<< orphan*/  status; void* res_number; void* access_type; void* res_id; } ;
struct TYPE_3__ {struct ice_aqc_req_res res_owner; } ;
struct ice_aq_desc {TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_aq_res_ids { ____Placeholder_ice_aq_res_ids } ice_aq_res_ids ;
typedef  enum ice_aq_res_access_type { ____Placeholder_ice_aq_res_access_type } ice_aq_res_access_type ;

/* Variables and functions */
 scalar_t__ ICE_AQ_RC_EBUSY ; 
 scalar_t__ ICE_AQ_RES_GLBL_DONE ; 
 scalar_t__ ICE_AQ_RES_GLBL_IN_PROG ; 
 scalar_t__ ICE_AQ_RES_GLBL_SUCCESS ; 
 int ICE_ERR_AQ_ERROR ; 
 int ICE_ERR_AQ_NO_WORK ; 
 int ICE_GLOBAL_CFG_LOCK_RES_ID ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_req_res ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 

__attribute__((used)) static enum ice_status
ice_aq_req_res(struct ice_hw *hw, enum ice_aq_res_ids res,
	       enum ice_aq_res_access_type access, u8 sdp_number, u32 *timeout,
	       struct ice_sq_cd *cd)
{
	struct ice_aqc_req_res *cmd_resp;
	struct ice_aq_desc desc;
	enum ice_status status;

	cmd_resp = &desc.params.res_owner;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_req_res);

	cmd_resp->res_id = cpu_to_le16(res);
	cmd_resp->access_type = cpu_to_le16(access);
	cmd_resp->res_number = cpu_to_le32(sdp_number);
	cmd_resp->timeout = cpu_to_le32(*timeout);
	*timeout = 0;

	status = ice_aq_send_cmd(hw, &desc, NULL, 0, cd);

	/* The completion specifies the maximum time in ms that the driver
	 * may hold the resource in the Timeout field.
	 */

	/* Global config lock response utilizes an additional status field.
	 *
	 * If the Global config lock resource is held by some other driver, the
	 * command completes with ICE_AQ_RES_GLBL_IN_PROG in the status field
	 * and the timeout field indicates the maximum time the current owner
	 * of the resource has to free it.
	 */
	if (res == ICE_GLOBAL_CFG_LOCK_RES_ID) {
		if (le16_to_cpu(cmd_resp->status) == ICE_AQ_RES_GLBL_SUCCESS) {
			*timeout = le32_to_cpu(cmd_resp->timeout);
			return 0;
		} else if (le16_to_cpu(cmd_resp->status) ==
			   ICE_AQ_RES_GLBL_IN_PROG) {
			*timeout = le32_to_cpu(cmd_resp->timeout);
			return ICE_ERR_AQ_ERROR;
		} else if (le16_to_cpu(cmd_resp->status) ==
			   ICE_AQ_RES_GLBL_DONE) {
			return ICE_ERR_AQ_NO_WORK;
		}

		/* invalid FW response, force a timeout immediately */
		*timeout = 0;
		return ICE_ERR_AQ_ERROR;
	}

	/* If the resource is held by some other driver, the command completes
	 * with a busy return value and the timeout field indicates the maximum
	 * time the current owner of the resource has to free it.
	 */
	if (!status || hw->adminq.sq_last_status == ICE_AQ_RC_EBUSY)
		*timeout = le32_to_cpu(cmd_resp->timeout);

	return status;
}