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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct devx_obj {scalar_t__ obj_id; } ;

/* Variables and functions */
#define  MLX5_CMD_OP_2ERR_QP 174 
#define  MLX5_CMD_OP_2RST_QP 173 
#define  MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT 172 
#define  MLX5_CMD_OP_ARM_DCT_FOR_KEY_VIOLATION 171 
#define  MLX5_CMD_OP_ARM_RQ 170 
#define  MLX5_CMD_OP_ARM_XRC_SRQ 169 
#define  MLX5_CMD_OP_ARM_XRQ 168 
#define  MLX5_CMD_OP_DRAIN_DCT 167 
#define  MLX5_CMD_OP_INIT2RTR_QP 166 
#define  MLX5_CMD_OP_MODIFY_CQ 165 
#define  MLX5_CMD_OP_MODIFY_FLOW_TABLE 164 
#define  MLX5_CMD_OP_MODIFY_GENERAL_OBJECT 163 
#define  MLX5_CMD_OP_MODIFY_RMP 162 
#define  MLX5_CMD_OP_MODIFY_RQ 161 
#define  MLX5_CMD_OP_MODIFY_RQT 160 
#define  MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT 159 
#define  MLX5_CMD_OP_MODIFY_SQ 158 
#define  MLX5_CMD_OP_MODIFY_TIR 157 
#define  MLX5_CMD_OP_MODIFY_TIS 156 
#define  MLX5_CMD_OP_QUERY_CQ 155 
#define  MLX5_CMD_OP_QUERY_DCT 154 
#define  MLX5_CMD_OP_QUERY_FLOW_COUNTER 153 
#define  MLX5_CMD_OP_QUERY_FLOW_GROUP 152 
#define  MLX5_CMD_OP_QUERY_FLOW_TABLE 151 
#define  MLX5_CMD_OP_QUERY_FLOW_TABLE_ENTRY 150 
#define  MLX5_CMD_OP_QUERY_GENERAL_OBJECT 149 
#define  MLX5_CMD_OP_QUERY_L2_TABLE_ENTRY 148 
#define  MLX5_CMD_OP_QUERY_MKEY 147 
#define  MLX5_CMD_OP_QUERY_MODIFY_HEADER_CONTEXT 146 
#define  MLX5_CMD_OP_QUERY_QP 145 
#define  MLX5_CMD_OP_QUERY_Q_COUNTER 144 
#define  MLX5_CMD_OP_QUERY_RMP 143 
#define  MLX5_CMD_OP_QUERY_RQ 142 
#define  MLX5_CMD_OP_QUERY_RQT 141 
#define  MLX5_CMD_OP_QUERY_SCHEDULING_ELEMENT 140 
#define  MLX5_CMD_OP_QUERY_SQ 139 
#define  MLX5_CMD_OP_QUERY_SRQ 138 
#define  MLX5_CMD_OP_QUERY_TIR 137 
#define  MLX5_CMD_OP_QUERY_TIS 136 
#define  MLX5_CMD_OP_QUERY_XRC_SRQ 135 
#define  MLX5_CMD_OP_QUERY_XRQ 134 
#define  MLX5_CMD_OP_RST2INIT_QP 133 
#define  MLX5_CMD_OP_RTR2RTS_QP 132 
#define  MLX5_CMD_OP_RTS2RTS_QP 131 
#define  MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY 130 
#define  MLX5_CMD_OP_SET_L2_TABLE_ENTRY 129 
#define  MLX5_CMD_OP_SQERR2RTS_QP 128 
 void* MLX5_GET (int /*<<< orphan*/ ,void const*,scalar_t__) ; 
 int /*<<< orphan*/  add_vxlan_udp_dport_in ; 
 int /*<<< orphan*/  arm_rq_in ; 
 int /*<<< orphan*/  arm_xrc_srq_in ; 
 int /*<<< orphan*/  arm_xrq_in ; 
 scalar_t__ counter_set_id ; 
 scalar_t__ cqn ; 
 scalar_t__ dctn ; 
 int /*<<< orphan*/  drain_dct_in ; 
 scalar_t__ flow_counter_id ; 
 scalar_t__ flow_index ; 
 int /*<<< orphan*/  general_obj_in_cmd_hdr ; 
 scalar_t__ group_id ; 
 int /*<<< orphan*/  init2rtr_qp_in ; 
 scalar_t__ mkey_index ; 
 int /*<<< orphan*/  modify_cq_in ; 
 int /*<<< orphan*/  modify_flow_table_in ; 
 int /*<<< orphan*/  modify_rmp_in ; 
 int /*<<< orphan*/  modify_rq_in ; 
 int /*<<< orphan*/  modify_rqt_in ; 
 int /*<<< orphan*/  modify_scheduling_element_in ; 
 int /*<<< orphan*/  modify_sq_in ; 
 int /*<<< orphan*/  modify_tir_in ; 
 int /*<<< orphan*/  modify_tis_in ; 
 int opcode ; 
 int /*<<< orphan*/  qp_2err_in ; 
 int /*<<< orphan*/  qp_2rst_in ; 
 scalar_t__ qpn ; 
 int /*<<< orphan*/  query_cq_in ; 
 int /*<<< orphan*/  query_dct_in ; 
 int /*<<< orphan*/  query_flow_counter_in ; 
 int /*<<< orphan*/  query_flow_group_in ; 
 int /*<<< orphan*/  query_flow_table_in ; 
 int /*<<< orphan*/  query_fte_in ; 
 int /*<<< orphan*/  query_l2_table_entry_in ; 
 int /*<<< orphan*/  query_mkey_in ; 
 int /*<<< orphan*/  query_q_counter_in ; 
 int /*<<< orphan*/  query_qp_in ; 
 int /*<<< orphan*/  query_rmp_in ; 
 int /*<<< orphan*/  query_rq_in ; 
 int /*<<< orphan*/  query_rqt_in ; 
 int /*<<< orphan*/  query_scheduling_element_in ; 
 int /*<<< orphan*/  query_sq_in ; 
 int /*<<< orphan*/  query_srq_in ; 
 int /*<<< orphan*/  query_tir_in ; 
 int /*<<< orphan*/  query_tis_in ; 
 int /*<<< orphan*/  query_xrc_srq_in ; 
 int /*<<< orphan*/  query_xrq_in ; 
 scalar_t__ rmpn ; 
 scalar_t__ rqn ; 
 scalar_t__ rqtn ; 
 int /*<<< orphan*/  rst2init_qp_in ; 
 int /*<<< orphan*/  rtr2rts_qp_in ; 
 int /*<<< orphan*/  rts2rts_qp_in ; 
 scalar_t__ scheduling_element_id ; 
 int /*<<< orphan*/  set_fte_in ; 
 int /*<<< orphan*/  set_l2_table_entry_in ; 
 int /*<<< orphan*/  sqerr2rts_qp_in ; 
 scalar_t__ sqn ; 
 scalar_t__ srq_number ; 
 scalar_t__ srqn ; 
 scalar_t__ table_id ; 
 scalar_t__ table_index ; 
 scalar_t__ tirn ; 
 scalar_t__ tisn ; 
 scalar_t__ vxlan_udp_port ; 
 scalar_t__ xrc_srqn ; 
 scalar_t__ xrqn ; 

__attribute__((used)) static int devx_is_valid_obj_id(struct devx_obj *obj, const void *in)
{
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);
	u32 obj_id;

	switch (opcode) {
	case MLX5_CMD_OP_MODIFY_GENERAL_OBJECT:
	case MLX5_CMD_OP_QUERY_GENERAL_OBJECT:
		obj_id = MLX5_GET(general_obj_in_cmd_hdr, in, obj_id);
		break;
	case MLX5_CMD_OP_QUERY_MKEY:
		obj_id = MLX5_GET(query_mkey_in, in, mkey_index);
		break;
	case MLX5_CMD_OP_QUERY_CQ:
		obj_id = MLX5_GET(query_cq_in, in, cqn);
		break;
	case MLX5_CMD_OP_MODIFY_CQ:
		obj_id = MLX5_GET(modify_cq_in, in, cqn);
		break;
	case MLX5_CMD_OP_QUERY_SQ:
		obj_id = MLX5_GET(query_sq_in, in, sqn);
		break;
	case MLX5_CMD_OP_MODIFY_SQ:
		obj_id = MLX5_GET(modify_sq_in, in, sqn);
		break;
	case MLX5_CMD_OP_QUERY_RQ:
		obj_id = MLX5_GET(query_rq_in, in, rqn);
		break;
	case MLX5_CMD_OP_MODIFY_RQ:
		obj_id = MLX5_GET(modify_rq_in, in, rqn);
		break;
	case MLX5_CMD_OP_QUERY_RMP:
		obj_id = MLX5_GET(query_rmp_in, in, rmpn);
		break;
	case MLX5_CMD_OP_MODIFY_RMP:
		obj_id = MLX5_GET(modify_rmp_in, in, rmpn);
		break;
	case MLX5_CMD_OP_QUERY_RQT:
		obj_id = MLX5_GET(query_rqt_in, in, rqtn);
		break;
	case MLX5_CMD_OP_MODIFY_RQT:
		obj_id = MLX5_GET(modify_rqt_in, in, rqtn);
		break;
	case MLX5_CMD_OP_QUERY_TIR:
		obj_id = MLX5_GET(query_tir_in, in, tirn);
		break;
	case MLX5_CMD_OP_MODIFY_TIR:
		obj_id = MLX5_GET(modify_tir_in, in, tirn);
		break;
	case MLX5_CMD_OP_QUERY_TIS:
		obj_id = MLX5_GET(query_tis_in, in, tisn);
		break;
	case MLX5_CMD_OP_MODIFY_TIS:
		obj_id = MLX5_GET(modify_tis_in, in, tisn);
		break;
	case MLX5_CMD_OP_QUERY_FLOW_TABLE:
		obj_id = MLX5_GET(query_flow_table_in, in, table_id);
		break;
	case MLX5_CMD_OP_MODIFY_FLOW_TABLE:
		obj_id = MLX5_GET(modify_flow_table_in, in, table_id);
		break;
	case MLX5_CMD_OP_QUERY_FLOW_GROUP:
		obj_id = MLX5_GET(query_flow_group_in, in, group_id);
		break;
	case MLX5_CMD_OP_QUERY_FLOW_TABLE_ENTRY:
		obj_id = MLX5_GET(query_fte_in, in, flow_index);
		break;
	case MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY:
		obj_id = MLX5_GET(set_fte_in, in, flow_index);
		break;
	case MLX5_CMD_OP_QUERY_Q_COUNTER:
		obj_id = MLX5_GET(query_q_counter_in, in, counter_set_id);
		break;
	case MLX5_CMD_OP_QUERY_FLOW_COUNTER:
		obj_id = MLX5_GET(query_flow_counter_in, in, flow_counter_id);
		break;
	case MLX5_CMD_OP_QUERY_MODIFY_HEADER_CONTEXT:
		obj_id = MLX5_GET(general_obj_in_cmd_hdr, in, obj_id);
		break;
	case MLX5_CMD_OP_QUERY_SCHEDULING_ELEMENT:
		obj_id = MLX5_GET(query_scheduling_element_in, in,
				  scheduling_element_id);
		break;
	case MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT:
		obj_id = MLX5_GET(modify_scheduling_element_in, in,
				  scheduling_element_id);
		break;
	case MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT:
		obj_id = MLX5_GET(add_vxlan_udp_dport_in, in, vxlan_udp_port);
		break;
	case MLX5_CMD_OP_QUERY_L2_TABLE_ENTRY:
		obj_id = MLX5_GET(query_l2_table_entry_in, in, table_index);
		break;
	case MLX5_CMD_OP_SET_L2_TABLE_ENTRY:
		obj_id = MLX5_GET(set_l2_table_entry_in, in, table_index);
		break;
	case MLX5_CMD_OP_QUERY_QP:
		obj_id = MLX5_GET(query_qp_in, in, qpn);
		break;
	case MLX5_CMD_OP_RST2INIT_QP:
		obj_id = MLX5_GET(rst2init_qp_in, in, qpn);
		break;
	case MLX5_CMD_OP_INIT2RTR_QP:
		obj_id = MLX5_GET(init2rtr_qp_in, in, qpn);
		break;
	case MLX5_CMD_OP_RTR2RTS_QP:
		obj_id = MLX5_GET(rtr2rts_qp_in, in, qpn);
		break;
	case MLX5_CMD_OP_RTS2RTS_QP:
		obj_id = MLX5_GET(rts2rts_qp_in, in, qpn);
		break;
	case MLX5_CMD_OP_SQERR2RTS_QP:
		obj_id = MLX5_GET(sqerr2rts_qp_in, in, qpn);
		break;
	case MLX5_CMD_OP_2ERR_QP:
		obj_id = MLX5_GET(qp_2err_in, in, qpn);
		break;
	case MLX5_CMD_OP_2RST_QP:
		obj_id = MLX5_GET(qp_2rst_in, in, qpn);
		break;
	case MLX5_CMD_OP_QUERY_DCT:
		obj_id = MLX5_GET(query_dct_in, in, dctn);
		break;
	case MLX5_CMD_OP_QUERY_XRQ:
		obj_id = MLX5_GET(query_xrq_in, in, xrqn);
		break;
	case MLX5_CMD_OP_QUERY_XRC_SRQ:
		obj_id = MLX5_GET(query_xrc_srq_in, in, xrc_srqn);
		break;
	case MLX5_CMD_OP_ARM_XRC_SRQ:
		obj_id = MLX5_GET(arm_xrc_srq_in, in, xrc_srqn);
		break;
	case MLX5_CMD_OP_QUERY_SRQ:
		obj_id = MLX5_GET(query_srq_in, in, srqn);
		break;
	case MLX5_CMD_OP_ARM_RQ:
		obj_id = MLX5_GET(arm_rq_in, in, srq_number);
		break;
	case MLX5_CMD_OP_DRAIN_DCT:
	case MLX5_CMD_OP_ARM_DCT_FOR_KEY_VIOLATION:
		obj_id = MLX5_GET(drain_dct_in, in, dctn);
		break;
	case MLX5_CMD_OP_ARM_XRQ:
		obj_id = MLX5_GET(arm_xrq_in, in, xrqn);
		break;
	default:
		return false;
	}

	if (obj_id == obj->obj_id)
		return true;

	return false;
}