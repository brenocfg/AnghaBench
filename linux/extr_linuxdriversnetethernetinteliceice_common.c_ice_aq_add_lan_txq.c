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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_add_txqs_perq {int dummy; } ;
struct ice_aqc_add_txqs {scalar_t__ num_qgrps; } ;
struct ice_aqc_add_tx_qgrp {int num_txqs; struct ice_aqc_add_txqs_perq* txqs; } ;
struct TYPE_2__ {struct ice_aqc_add_txqs add_txqs; } ;
struct ice_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_FLAG_RD ; 
 int ICE_ERR_PARAM ; 
 scalar_t__ ICE_LAN_TXQ_MAX_QGRPS ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,struct ice_aqc_add_tx_qgrp*,scalar_t__,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_add_txqs ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_aq_add_lan_txq(struct ice_hw *hw, u8 num_qgrps,
		   struct ice_aqc_add_tx_qgrp *qg_list, u16 buf_size,
		   struct ice_sq_cd *cd)
{
	u16 i, sum_header_size, sum_q_size = 0;
	struct ice_aqc_add_tx_qgrp *list;
	struct ice_aqc_add_txqs *cmd;
	struct ice_aq_desc desc;

	cmd = &desc.params.add_txqs;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_add_txqs);

	if (!qg_list)
		return ICE_ERR_PARAM;

	if (num_qgrps > ICE_LAN_TXQ_MAX_QGRPS)
		return ICE_ERR_PARAM;

	sum_header_size = num_qgrps *
		(sizeof(*qg_list) - sizeof(*qg_list->txqs));

	list = qg_list;
	for (i = 0; i < num_qgrps; i++) {
		struct ice_aqc_add_txqs_perq *q = list->txqs;

		sum_q_size += list->num_txqs * sizeof(*q);
		list = (struct ice_aqc_add_tx_qgrp *)(q + list->num_txqs);
	}

	if (buf_size != (sum_header_size + sum_q_size))
		return ICE_ERR_PARAM;

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	cmd->num_qgrps = num_qgrps;

	return ice_aq_send_cmd(hw, &desc, qg_list, buf_size, cd);
}