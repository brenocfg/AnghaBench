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
struct ice_port_info {scalar_t__ port_state; int /*<<< orphan*/  sched_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  root; } ;
struct ice_aqc_dis_txq_item {int num_qs; int /*<<< orphan*/ * q_id; int /*<<< orphan*/  parent_teid; } ;
typedef  int /*<<< orphan*/  qg_list ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_CFG ; 
 int ICE_ERR_DOES_NOT_EXIST ; 
 scalar_t__ ICE_SCHED_PORT_STATE_READY ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 int ice_aq_dis_lan_txq (int /*<<< orphan*/ ,int,struct ice_aqc_dis_txq_item*,int,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_free_sched_node (struct ice_port_info*,struct ice_sched_node*) ; 
 struct ice_sched_node* ice_sched_find_node_by_teid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

enum ice_status
ice_dis_vsi_txq(struct ice_port_info *pi, u8 num_queues, u16 *q_ids,
		u32 *q_teids, struct ice_sq_cd *cd)
{
	enum ice_status status = ICE_ERR_DOES_NOT_EXIST;
	struct ice_aqc_dis_txq_item qg_list;
	u16 i;

	if (!pi || pi->port_state != ICE_SCHED_PORT_STATE_READY)
		return ICE_ERR_CFG;

	mutex_lock(&pi->sched_lock);

	for (i = 0; i < num_queues; i++) {
		struct ice_sched_node *node;

		node = ice_sched_find_node_by_teid(pi->root, q_teids[i]);
		if (!node)
			continue;
		qg_list.parent_teid = node->info.parent_teid;
		qg_list.num_qs = 1;
		qg_list.q_id[0] = cpu_to_le16(q_ids[i]);
		status = ice_aq_dis_lan_txq(pi->hw, 1, &qg_list,
					    sizeof(qg_list), cd);

		if (status)
			break;
		ice_free_sched_node(pi, node);
	}
	mutex_unlock(&pi->sched_lock);
	return status;
}