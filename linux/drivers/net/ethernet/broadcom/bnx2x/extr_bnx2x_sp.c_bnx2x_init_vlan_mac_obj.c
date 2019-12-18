#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  union bnx2x_qable_obj {int dummy; } bnx2x_qable_obj ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x_vlan_mac_obj {int /*<<< orphan*/  exe_queue; int /*<<< orphan*/  ramrod_cmd; int /*<<< orphan*/  check_move; void* check_add; void* check_del; int /*<<< orphan*/  set_one_rule; int /*<<< orphan*/  put_cam_offset; int /*<<< orphan*/  get_cam_offset; int /*<<< orphan*/  put_credit; int /*<<< orphan*/  get_credit; } ;
struct bnx2x_credit_pool_obj {int dummy; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  bnx2x_obj_type ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1H (struct bnx2x*) ; 
 int CLASSIFY_RULES_COUNT ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_SET_MAC ; 
 int /*<<< orphan*/  bnx2x_check_move ; 
 int /*<<< orphan*/  bnx2x_check_move_always_err ; 
 void* bnx2x_check_vlan_mac_add ; 
 void* bnx2x_check_vlan_mac_del ; 
 int /*<<< orphan*/  bnx2x_exe_queue_init (struct bnx2x*,int /*<<< orphan*/ *,int,union bnx2x_qable_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_execute_vlan_mac ; 
 int /*<<< orphan*/  bnx2x_exeq_get_vlan_mac ; 
 int /*<<< orphan*/  bnx2x_get_cam_offset_mac ; 
 int /*<<< orphan*/  bnx2x_get_credit_vlan_mac ; 
 int /*<<< orphan*/  bnx2x_init_vlan_mac_common (struct bnx2x_vlan_mac_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,unsigned long*,int /*<<< orphan*/ ,struct bnx2x_credit_pool_obj*,struct bnx2x_credit_pool_obj*) ; 
 int /*<<< orphan*/  bnx2x_optimize_vlan_mac ; 
 int /*<<< orphan*/  bnx2x_put_cam_offset_mac ; 
 int /*<<< orphan*/  bnx2x_put_credit_vlan_mac ; 
 int /*<<< orphan*/  bnx2x_remove_vlan_mac ; 
 int /*<<< orphan*/  bnx2x_set_one_vlan_mac_e1h ; 
 int /*<<< orphan*/  bnx2x_set_one_vlan_mac_e2 ; 
 int /*<<< orphan*/  bnx2x_validate_vlan_mac ; 

void bnx2x_init_vlan_mac_obj(struct bnx2x *bp,
			     struct bnx2x_vlan_mac_obj *vlan_mac_obj,
			     u8 cl_id, u32 cid, u8 func_id, void *rdata,
			     dma_addr_t rdata_mapping, int state,
			     unsigned long *pstate, bnx2x_obj_type type,
			     struct bnx2x_credit_pool_obj *macs_pool,
			     struct bnx2x_credit_pool_obj *vlans_pool)
{
	union bnx2x_qable_obj *qable_obj =
		(union bnx2x_qable_obj *)vlan_mac_obj;

	bnx2x_init_vlan_mac_common(vlan_mac_obj, cl_id, cid, func_id, rdata,
				   rdata_mapping, state, pstate, type,
				   macs_pool, vlans_pool);

	/* CAM pool handling */
	vlan_mac_obj->get_credit = bnx2x_get_credit_vlan_mac;
	vlan_mac_obj->put_credit = bnx2x_put_credit_vlan_mac;
	/* CAM offset is relevant for 57710 and 57711 chips only which have a
	 * single CAM for both MACs and VLAN-MAC pairs. So the offset
	 * will be taken from MACs' pool object only.
	 */
	vlan_mac_obj->get_cam_offset = bnx2x_get_cam_offset_mac;
	vlan_mac_obj->put_cam_offset = bnx2x_put_cam_offset_mac;

	if (CHIP_IS_E1(bp)) {
		BNX2X_ERR("Do not support chips others than E2\n");
		BUG();
	} else if (CHIP_IS_E1H(bp)) {
		vlan_mac_obj->set_one_rule      = bnx2x_set_one_vlan_mac_e1h;
		vlan_mac_obj->check_del         = bnx2x_check_vlan_mac_del;
		vlan_mac_obj->check_add         = bnx2x_check_vlan_mac_add;
		vlan_mac_obj->check_move        = bnx2x_check_move_always_err;
		vlan_mac_obj->ramrod_cmd        = RAMROD_CMD_ID_ETH_SET_MAC;

		/* Exe Queue */
		bnx2x_exe_queue_init(bp,
				     &vlan_mac_obj->exe_queue, 1, qable_obj,
				     bnx2x_validate_vlan_mac,
				     bnx2x_remove_vlan_mac,
				     bnx2x_optimize_vlan_mac,
				     bnx2x_execute_vlan_mac,
				     bnx2x_exeq_get_vlan_mac);
	} else {
		vlan_mac_obj->set_one_rule      = bnx2x_set_one_vlan_mac_e2;
		vlan_mac_obj->check_del         = bnx2x_check_vlan_mac_del;
		vlan_mac_obj->check_add         = bnx2x_check_vlan_mac_add;
		vlan_mac_obj->check_move        = bnx2x_check_move;
		vlan_mac_obj->ramrod_cmd        =
			RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES;

		/* Exe Queue */
		bnx2x_exe_queue_init(bp,
				     &vlan_mac_obj->exe_queue,
				     CLASSIFY_RULES_COUNT,
				     qable_obj, bnx2x_validate_vlan_mac,
				     bnx2x_remove_vlan_mac,
				     bnx2x_optimize_vlan_mac,
				     bnx2x_execute_vlan_mac,
				     bnx2x_exeq_get_vlan_mac);
	}
}