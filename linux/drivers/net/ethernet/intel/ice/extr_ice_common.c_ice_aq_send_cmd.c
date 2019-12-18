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
struct ice_hw {int /*<<< orphan*/  adminq; } ;
struct ice_aqc_req_res {int /*<<< orphan*/  res_id; } ;
struct TYPE_2__ {struct ice_aqc_req_res res_owner; } ;
struct ice_aq_desc {int /*<<< orphan*/  opcode; TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_AQC_RES_ID_GLBL_LOCK ; 
#define  ice_aqc_opc_download_pkg 131 
#define  ice_aqc_opc_get_pkg_info_list 130 
#define  ice_aqc_opc_get_ver 129 
#define  ice_aqc_opc_release_res 128 
 int /*<<< orphan*/  ice_global_cfg_lock_sw ; 
 int ice_sq_send_cmd (struct ice_hw*,int /*<<< orphan*/ *,struct ice_aq_desc*,void*,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

enum ice_status
ice_aq_send_cmd(struct ice_hw *hw, struct ice_aq_desc *desc, void *buf,
		u16 buf_size, struct ice_sq_cd *cd)
{
	struct ice_aqc_req_res *cmd = &desc->params.res_owner;
	bool lock_acquired = false;
	enum ice_status status;

	/* When a package download is in process (i.e. when the firmware's
	 * Global Configuration Lock resource is held), only the Download
	 * Package, Get Version, Get Package Info List and Release Resource
	 * (with resource ID set to Global Config Lock) AdminQ commands are
	 * allowed; all others must block until the package download completes
	 * and the Global Config Lock is released.  See also
	 * ice_acquire_global_cfg_lock().
	 */
	switch (le16_to_cpu(desc->opcode)) {
	case ice_aqc_opc_download_pkg:
	case ice_aqc_opc_get_pkg_info_list:
	case ice_aqc_opc_get_ver:
		break;
	case ice_aqc_opc_release_res:
		if (le16_to_cpu(cmd->res_id) == ICE_AQC_RES_ID_GLBL_LOCK)
			break;
		/* fall-through */
	default:
		mutex_lock(&ice_global_cfg_lock_sw);
		lock_acquired = true;
		break;
	}

	status = ice_sq_send_cmd(hw, &hw->adminq, desc, buf, buf_size, cd);
	if (lock_acquired)
		mutex_unlock(&ice_global_cfg_lock_sw);

	return status;
}