#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct ice_sq_cd {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sq_last_status; } ;
struct TYPE_5__ {scalar_t__ vf_base_id; } ;
struct ice_hw {TYPE_3__ adminq; TYPE_2__ func_caps; } ;
struct ice_aqc_dis_txqs {int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  vmvf_and_timeout; scalar_t__ num_entries; } ;
struct ice_aqc_dis_txq_item {int num_qs; int /*<<< orphan*/ * q_id; } ;
struct TYPE_4__ {struct ice_aqc_dis_txqs dis_txqs; } ;
struct ice_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  qg_list ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_disq_rst_src { ____Placeholder_ice_disq_rst_src } ice_disq_rst_src ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQC_Q_DIS_CMD_FLUSH_PIPE ; 
 int /*<<< orphan*/  ICE_AQC_Q_DIS_CMD_VF_RESET ; 
 int /*<<< orphan*/  ICE_AQC_Q_DIS_CMD_VM_RESET ; 
 int ICE_AQC_Q_DIS_TIMEOUT_M ; 
 int ICE_AQC_Q_DIS_TIMEOUT_S ; 
 scalar_t__ ICE_AQC_Q_DIS_VMVF_NUM_M ; 
 scalar_t__ ICE_AQ_FLAG_RD ; 
 int /*<<< orphan*/  ICE_DBG_SCHED ; 
 int ICE_ERR_PARAM ; 
 scalar_t__ ICE_LAN_TXQ_MAX_QGRPS ; 
#define  ICE_NO_RESET 130 
#define  ICE_VF_RESET 129 
#define  ICE_VM_RESET 128 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int ice_aq_send_cmd (struct ice_hw*,struct ice_aq_desc*,struct ice_aqc_dis_txq_item*,scalar_t__,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_aqc_opc_dis_txqs ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_aq_dis_lan_txq(struct ice_hw *hw, u8 num_qgrps,
		   struct ice_aqc_dis_txq_item *qg_list, u16 buf_size,
		   enum ice_disq_rst_src rst_src, u16 vmvf_num,
		   struct ice_sq_cd *cd)
{
	struct ice_aqc_dis_txqs *cmd;
	struct ice_aq_desc desc;
	enum ice_status status;
	u16 i, sz = 0;

	cmd = &desc.params.dis_txqs;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_dis_txqs);

	/* qg_list can be NULL only in VM/VF reset flow */
	if (!qg_list && !rst_src)
		return ICE_ERR_PARAM;

	if (num_qgrps > ICE_LAN_TXQ_MAX_QGRPS)
		return ICE_ERR_PARAM;

	cmd->num_entries = num_qgrps;

	cmd->vmvf_and_timeout = cpu_to_le16((5 << ICE_AQC_Q_DIS_TIMEOUT_S) &
					    ICE_AQC_Q_DIS_TIMEOUT_M);

	switch (rst_src) {
	case ICE_VM_RESET:
		cmd->cmd_type = ICE_AQC_Q_DIS_CMD_VM_RESET;
		cmd->vmvf_and_timeout |=
			cpu_to_le16(vmvf_num & ICE_AQC_Q_DIS_VMVF_NUM_M);
		break;
	case ICE_VF_RESET:
		cmd->cmd_type = ICE_AQC_Q_DIS_CMD_VF_RESET;
		/* In this case, FW expects vmvf_num to be absolute VF ID */
		cmd->vmvf_and_timeout |=
			cpu_to_le16((vmvf_num + hw->func_caps.vf_base_id) &
				    ICE_AQC_Q_DIS_VMVF_NUM_M);
		break;
	case ICE_NO_RESET:
	default:
		break;
	}

	/* flush pipe on time out */
	cmd->cmd_type |= ICE_AQC_Q_DIS_CMD_FLUSH_PIPE;
	/* If no queue group info, we are in a reset flow. Issue the AQ */
	if (!qg_list)
		goto do_aq;

	/* set RD bit to indicate that command buffer is provided by the driver
	 * and it needs to be read by the firmware
	 */
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	for (i = 0; i < num_qgrps; ++i) {
		/* Calculate the size taken up by the queue IDs in this group */
		sz += qg_list[i].num_qs * sizeof(qg_list[i].q_id);

		/* Add the size of the group header */
		sz += sizeof(qg_list[i]) - sizeof(qg_list[i].q_id);

		/* If the num of queues is even, add 2 bytes of padding */
		if ((qg_list[i].num_qs % 2) == 0)
			sz += 2;
	}

	if (buf_size != sz)
		return ICE_ERR_PARAM;

do_aq:
	status = ice_aq_send_cmd(hw, &desc, qg_list, buf_size, cd);
	if (status) {
		if (!qg_list)
			ice_debug(hw, ICE_DBG_SCHED, "VM%d disable failed %d\n",
				  vmvf_num, hw->adminq.sq_last_status);
		else
			ice_debug(hw, ICE_DBG_SCHED, "disable queue %d failed %d\n",
				  le16_to_cpu(qg_list[0].q_id[0]),
				  hw->adminq.sq_last_status);
	}
	return status;
}