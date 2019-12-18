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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct ice_sq_cd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent_teid; } ;
struct ice_sched_node {TYPE_1__ info; } ;
struct ice_q_ctx {size_t q_handle; } ;
struct ice_port_info {scalar_t__ port_state; int /*<<< orphan*/  sched_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  root; } ;
struct ice_aqc_dis_txq_item {int num_qs; int /*<<< orphan*/ * q_id; int /*<<< orphan*/  parent_teid; } ;
typedef  int /*<<< orphan*/  qg_list ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_disq_rst_src { ____Placeholder_ice_disq_rst_src } ice_disq_rst_src ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DBG_SCHED ; 
 int ICE_ERR_CFG ; 
 int ICE_ERR_DOES_NOT_EXIST ; 
 size_t ICE_INVAL_Q_HANDLE ; 
 scalar_t__ ICE_SCHED_PORT_STATE_READY ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 int ice_aq_dis_lan_txq (int /*<<< orphan*/ ,int,struct ice_aqc_dis_txq_item*,int,int,size_t,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  ice_free_sched_node (struct ice_port_info*,struct ice_sched_node*) ; 
 struct ice_q_ctx* ice_get_lan_q_ctx (int /*<<< orphan*/ ,size_t,size_t,size_t) ; 
 struct ice_sched_node* ice_sched_find_node_by_teid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

enum ice_status
ice_dis_vsi_txq(struct ice_port_info *pi, u16 vsi_handle, u8 tc, u8 num_queues,
		u16 *q_handles, u16 *q_ids, u32 *q_teids,
		enum ice_disq_rst_src rst_src, u16 vmvf_num,
		struct ice_sq_cd *cd)
{
	enum ice_status status = ICE_ERR_DOES_NOT_EXIST;
	struct ice_aqc_dis_txq_item qg_list;
	struct ice_q_ctx *q_ctx;
	u16 i;

	if (!pi || pi->port_state != ICE_SCHED_PORT_STATE_READY)
		return ICE_ERR_CFG;

	if (!num_queues) {
		/* if queue is disabled already yet the disable queue command
		 * has to be sent to complete the VF reset, then call
		 * ice_aq_dis_lan_txq without any queue information
		 */
		if (rst_src)
			return ice_aq_dis_lan_txq(pi->hw, 0, NULL, 0, rst_src,
						  vmvf_num, NULL);
		return ICE_ERR_CFG;
	}

	mutex_lock(&pi->sched_lock);

	for (i = 0; i < num_queues; i++) {
		struct ice_sched_node *node;

		node = ice_sched_find_node_by_teid(pi->root, q_teids[i]);
		if (!node)
			continue;
		q_ctx = ice_get_lan_q_ctx(pi->hw, vsi_handle, tc, q_handles[i]);
		if (!q_ctx) {
			ice_debug(pi->hw, ICE_DBG_SCHED, "invalid queue handle%d\n",
				  q_handles[i]);
			continue;
		}
		if (q_ctx->q_handle != q_handles[i]) {
			ice_debug(pi->hw, ICE_DBG_SCHED, "Err:handles %d %d\n",
				  q_ctx->q_handle, q_handles[i]);
			continue;
		}
		qg_list.parent_teid = node->info.parent_teid;
		qg_list.num_qs = 1;
		qg_list.q_id[0] = cpu_to_le16(q_ids[i]);
		status = ice_aq_dis_lan_txq(pi->hw, 1, &qg_list,
					    sizeof(qg_list), rst_src, vmvf_num,
					    cd);

		if (status)
			break;
		ice_free_sched_node(pi, node);
		q_ctx->q_handle = ICE_INVAL_Q_HANDLE;
	}
	mutex_unlock(&pi->sched_lock);
	return status;
}