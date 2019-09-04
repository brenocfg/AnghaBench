#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_sq_cd {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  node_teid; } ;
struct ice_sched_node {TYPE_1__ info; } ;
struct ice_port_info {scalar_t__ port_state; int /*<<< orphan*/  sched_lock; struct ice_hw* hw; } ;
struct ice_hw {scalar_t__ num_tx_sched_layers; } ;
struct TYPE_8__ {int /*<<< orphan*/  elem_type; } ;
struct ice_aqc_txsched_elem_data {TYPE_4__ data; int /*<<< orphan*/  node_teid; int /*<<< orphan*/  parent_teid; int /*<<< orphan*/  member_0; } ;
struct ice_aqc_add_tx_qgrp {int num_txqs; TYPE_3__* txqs; int /*<<< orphan*/  parent_teid; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_6__ {int /*<<< orphan*/  valid_sections; } ;
struct TYPE_7__ {int /*<<< orphan*/  q_teid; TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQC_ELEM_TYPE_LEAF ; 
 int /*<<< orphan*/  ICE_AQC_ELEM_VALID_GENERIC ; 
 int ICE_ERR_CFG ; 
 int ICE_ERR_MAX_LIMIT ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  ICE_SCHED_NODE_OWNER_LAN ; 
 scalar_t__ ICE_SCHED_PORT_STATE_READY ; 
 int ice_aq_add_lan_txq (struct ice_hw*,int,struct ice_aqc_add_tx_qgrp*,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int ice_sched_add_node (struct ice_port_info*,scalar_t__,struct ice_aqc_txsched_elem_data*) ; 
 struct ice_sched_node* ice_sched_get_free_qparent (struct ice_port_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

enum ice_status
ice_ena_vsi_txq(struct ice_port_info *pi, u16 vsi_id, u8 tc, u8 num_qgrps,
		struct ice_aqc_add_tx_qgrp *buf, u16 buf_size,
		struct ice_sq_cd *cd)
{
	struct ice_aqc_txsched_elem_data node = { 0 };
	struct ice_sched_node *parent;
	enum ice_status status;
	struct ice_hw *hw;

	if (!pi || pi->port_state != ICE_SCHED_PORT_STATE_READY)
		return ICE_ERR_CFG;

	if (num_qgrps > 1 || buf->num_txqs > 1)
		return ICE_ERR_MAX_LIMIT;

	hw = pi->hw;

	mutex_lock(&pi->sched_lock);

	/* find a parent node */
	parent = ice_sched_get_free_qparent(pi, vsi_id, tc,
					    ICE_SCHED_NODE_OWNER_LAN);
	if (!parent) {
		status = ICE_ERR_PARAM;
		goto ena_txq_exit;
	}
	buf->parent_teid = parent->info.node_teid;
	node.parent_teid = parent->info.node_teid;
	/* Mark that the values in the "generic" section as valid. The default
	 * value in the "generic" section is zero. This means that :
	 * - Scheduling mode is Bytes Per Second (BPS), indicated by Bit 0.
	 * - 0 priority among siblings, indicated by Bit 1-3.
	 * - WFQ, indicated by Bit 4.
	 * - 0 Adjustment value is used in PSM credit update flow, indicated by
	 * Bit 5-6.
	 * - Bit 7 is reserved.
	 * Without setting the generic section as valid in valid_sections, the
	 * Admin Q command will fail with error code ICE_AQ_RC_EINVAL.
	 */
	buf->txqs[0].info.valid_sections = ICE_AQC_ELEM_VALID_GENERIC;

	/* add the lan q */
	status = ice_aq_add_lan_txq(hw, num_qgrps, buf, buf_size, cd);
	if (status)
		goto ena_txq_exit;

	node.node_teid = buf->txqs[0].q_teid;
	node.data.elem_type = ICE_AQC_ELEM_TYPE_LEAF;

	/* add a leaf node into schduler tree q layer */
	status = ice_sched_add_node(pi, hw->num_tx_sched_layers - 1, &node);

ena_txq_exit:
	mutex_unlock(&pi->sched_lock);
	return status;
}