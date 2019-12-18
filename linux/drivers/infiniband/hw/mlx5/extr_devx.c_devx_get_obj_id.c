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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;

/* Variables and functions */
#define  MLX5_CMD_OP_2ERR_QP 179 
#define  MLX5_CMD_OP_2RST_QP 178 
#define  MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT 177 
 int const MLX5_CMD_OP_ALLOC_FLOW_COUNTER ; 
 int const MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT ; 
 int const MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT ; 
 int const MLX5_CMD_OP_ALLOC_Q_COUNTER ; 
#define  MLX5_CMD_OP_ARM_DCT_FOR_KEY_VIOLATION 176 
#define  MLX5_CMD_OP_ARM_RQ 175 
#define  MLX5_CMD_OP_ARM_XRC_SRQ 174 
#define  MLX5_CMD_OP_ARM_XRQ 173 
 int const MLX5_CMD_OP_CREATE_CQ ; 
 int const MLX5_CMD_OP_CREATE_DCT ; 
 int const MLX5_CMD_OP_CREATE_FLOW_GROUP ; 
 int const MLX5_CMD_OP_CREATE_FLOW_TABLE ; 
 int MLX5_CMD_OP_CREATE_GENERAL_OBJECT ; 
 int const MLX5_CMD_OP_CREATE_MKEY ; 
 int const MLX5_CMD_OP_CREATE_QP ; 
 int const MLX5_CMD_OP_CREATE_RMP ; 
 int const MLX5_CMD_OP_CREATE_RQ ; 
 int const MLX5_CMD_OP_CREATE_RQT ; 
 int const MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT ; 
 int const MLX5_CMD_OP_CREATE_SQ ; 
 int const MLX5_CMD_OP_CREATE_SRQ ; 
 int const MLX5_CMD_OP_CREATE_TIR ; 
 int const MLX5_CMD_OP_CREATE_TIS ; 
 int const MLX5_CMD_OP_CREATE_XRC_SRQ ; 
 int const MLX5_CMD_OP_CREATE_XRQ ; 
#define  MLX5_CMD_OP_INIT2RTR_QP 172 
#define  MLX5_CMD_OP_MODIFY_CQ 171 
#define  MLX5_CMD_OP_MODIFY_FLOW_TABLE 170 
#define  MLX5_CMD_OP_MODIFY_GENERAL_OBJECT 169 
#define  MLX5_CMD_OP_MODIFY_RMP 168 
#define  MLX5_CMD_OP_MODIFY_RQ 167 
#define  MLX5_CMD_OP_MODIFY_RQT 166 
#define  MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT 165 
#define  MLX5_CMD_OP_MODIFY_SQ 164 
#define  MLX5_CMD_OP_MODIFY_TIR 163 
#define  MLX5_CMD_OP_MODIFY_TIS 162 
#define  MLX5_CMD_OP_MODIFY_XRQ 161 
#define  MLX5_CMD_OP_QUERY_CQ 160 
#define  MLX5_CMD_OP_QUERY_DCT 159 
#define  MLX5_CMD_OP_QUERY_FLOW_COUNTER 158 
#define  MLX5_CMD_OP_QUERY_FLOW_GROUP 157 
#define  MLX5_CMD_OP_QUERY_FLOW_TABLE 156 
#define  MLX5_CMD_OP_QUERY_FLOW_TABLE_ENTRY 155 
#define  MLX5_CMD_OP_QUERY_GENERAL_OBJECT 154 
#define  MLX5_CMD_OP_QUERY_L2_TABLE_ENTRY 153 
#define  MLX5_CMD_OP_QUERY_MKEY 152 
#define  MLX5_CMD_OP_QUERY_MODIFY_HEADER_CONTEXT 151 
#define  MLX5_CMD_OP_QUERY_PACKET_REFORMAT_CONTEXT 150 
#define  MLX5_CMD_OP_QUERY_QP 149 
#define  MLX5_CMD_OP_QUERY_Q_COUNTER 148 
#define  MLX5_CMD_OP_QUERY_RMP 147 
#define  MLX5_CMD_OP_QUERY_RQ 146 
#define  MLX5_CMD_OP_QUERY_RQT 145 
#define  MLX5_CMD_OP_QUERY_SCHEDULING_ELEMENT 144 
#define  MLX5_CMD_OP_QUERY_SQ 143 
#define  MLX5_CMD_OP_QUERY_SRQ 142 
#define  MLX5_CMD_OP_QUERY_TIR 141 
#define  MLX5_CMD_OP_QUERY_TIS 140 
#define  MLX5_CMD_OP_QUERY_XRC_SRQ 139 
#define  MLX5_CMD_OP_QUERY_XRQ 138 
#define  MLX5_CMD_OP_QUERY_XRQ_DC_PARAMS_ENTRY 137 
#define  MLX5_CMD_OP_QUERY_XRQ_ERROR_PARAMS 136 
#define  MLX5_CMD_OP_RELEASE_XRQ_ERROR 135 
#define  MLX5_CMD_OP_RST2INIT_QP 134 
#define  MLX5_CMD_OP_RTR2RTS_QP 133 
#define  MLX5_CMD_OP_RTS2RTS_QP 132 
#define  MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY 131 
#define  MLX5_CMD_OP_SET_L2_TABLE_ENTRY 130 
#define  MLX5_CMD_OP_SET_XRQ_DC_PARAMS_ENTRY 129 
#define  MLX5_CMD_OP_SQERR2RTS_QP 128 
 int MLX5_GET (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_vxlan_udp_dport_in ; 
 int /*<<< orphan*/  arm_rq_in ; 
 int /*<<< orphan*/  arm_xrc_srq_in ; 
 int /*<<< orphan*/  arm_xrq_in ; 
 int /*<<< orphan*/  counter_set_id ; 
 int /*<<< orphan*/  cqn ; 
 int /*<<< orphan*/  dctn ; 
 int /*<<< orphan*/  drain_dct_in ; 
 int /*<<< orphan*/  flow_counter_id ; 
 int /*<<< orphan*/  flow_index ; 
 int /*<<< orphan*/  general_obj_in_cmd_hdr ; 
 int /*<<< orphan*/  get_enc_obj_id (int const,int) ; 
 int /*<<< orphan*/  group_id ; 
 int /*<<< orphan*/  init2rtr_qp_in ; 
 int /*<<< orphan*/  mkey_index ; 
 int /*<<< orphan*/  modify_cq_in ; 
 int /*<<< orphan*/  modify_flow_table_in ; 
 int /*<<< orphan*/  modify_rmp_in ; 
 int /*<<< orphan*/  modify_rq_in ; 
 int /*<<< orphan*/  modify_rqt_in ; 
 int /*<<< orphan*/  modify_scheduling_element_in ; 
 int /*<<< orphan*/  modify_sq_in ; 
 int /*<<< orphan*/  modify_tir_in ; 
 int /*<<< orphan*/  modify_tis_in ; 
 int /*<<< orphan*/  obj_type ; 
 int opcode ; 
 int /*<<< orphan*/  packet_reformat_id ; 
 int /*<<< orphan*/  qp_2err_in ; 
 int /*<<< orphan*/  qp_2rst_in ; 
 int /*<<< orphan*/  qpn ; 
 int /*<<< orphan*/  query_cq_in ; 
 int /*<<< orphan*/  query_dct_in ; 
 int /*<<< orphan*/  query_flow_counter_in ; 
 int /*<<< orphan*/  query_flow_group_in ; 
 int /*<<< orphan*/  query_flow_table_in ; 
 int /*<<< orphan*/  query_fte_in ; 
 int /*<<< orphan*/  query_l2_table_entry_in ; 
 int /*<<< orphan*/  query_mkey_in ; 
 int /*<<< orphan*/  query_packet_reformat_context_in ; 
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
 int /*<<< orphan*/  rmpn ; 
 int /*<<< orphan*/  rqn ; 
 int /*<<< orphan*/  rqtn ; 
 int /*<<< orphan*/  rst2init_qp_in ; 
 int /*<<< orphan*/  rtr2rts_qp_in ; 
 int /*<<< orphan*/  rts2rts_qp_in ; 
 int /*<<< orphan*/  scheduling_element_id ; 
 int /*<<< orphan*/  set_fte_in ; 
 int /*<<< orphan*/  set_l2_table_entry_in ; 
 int /*<<< orphan*/  sqerr2rts_qp_in ; 
 int /*<<< orphan*/  sqn ; 
 int /*<<< orphan*/  srq_number ; 
 int /*<<< orphan*/  srqn ; 
 int /*<<< orphan*/  table_id ; 
 int /*<<< orphan*/  table_index ; 
 int /*<<< orphan*/  tirn ; 
 int /*<<< orphan*/  tisn ; 
 int /*<<< orphan*/  vxlan_udp_port ; 
 int /*<<< orphan*/  xrc_srqn ; 
 int /*<<< orphan*/  xrqn ; 

__attribute__((used)) static u64 devx_get_obj_id(const void *in)
{
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);
	u64 obj_id;

	switch (opcode) {
	case MLX5_CMD_OP_MODIFY_GENERAL_OBJECT:
	case MLX5_CMD_OP_QUERY_GENERAL_OBJECT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_GENERAL_OBJECT |
					MLX5_GET(general_obj_in_cmd_hdr, in,
						 obj_type) << 16,
					MLX5_GET(general_obj_in_cmd_hdr, in,
						 obj_id));
		break;
	case MLX5_CMD_OP_QUERY_MKEY:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_MKEY,
					MLX5_GET(query_mkey_in, in,
						 mkey_index));
		break;
	case MLX5_CMD_OP_QUERY_CQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_CQ,
					MLX5_GET(query_cq_in, in, cqn));
		break;
	case MLX5_CMD_OP_MODIFY_CQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_CQ,
					MLX5_GET(modify_cq_in, in, cqn));
		break;
	case MLX5_CMD_OP_QUERY_SQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_SQ,
					MLX5_GET(query_sq_in, in, sqn));
		break;
	case MLX5_CMD_OP_MODIFY_SQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_SQ,
					MLX5_GET(modify_sq_in, in, sqn));
		break;
	case MLX5_CMD_OP_QUERY_RQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RQ,
					MLX5_GET(query_rq_in, in, rqn));
		break;
	case MLX5_CMD_OP_MODIFY_RQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RQ,
					MLX5_GET(modify_rq_in, in, rqn));
		break;
	case MLX5_CMD_OP_QUERY_RMP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RMP,
					MLX5_GET(query_rmp_in, in, rmpn));
		break;
	case MLX5_CMD_OP_MODIFY_RMP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RMP,
					MLX5_GET(modify_rmp_in, in, rmpn));
		break;
	case MLX5_CMD_OP_QUERY_RQT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RQT,
					MLX5_GET(query_rqt_in, in, rqtn));
		break;
	case MLX5_CMD_OP_MODIFY_RQT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RQT,
					MLX5_GET(modify_rqt_in, in, rqtn));
		break;
	case MLX5_CMD_OP_QUERY_TIR:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_TIR,
					MLX5_GET(query_tir_in, in, tirn));
		break;
	case MLX5_CMD_OP_MODIFY_TIR:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_TIR,
					MLX5_GET(modify_tir_in, in, tirn));
		break;
	case MLX5_CMD_OP_QUERY_TIS:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_TIS,
					MLX5_GET(query_tis_in, in, tisn));
		break;
	case MLX5_CMD_OP_MODIFY_TIS:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_TIS,
					MLX5_GET(modify_tis_in, in, tisn));
		break;
	case MLX5_CMD_OP_QUERY_FLOW_TABLE:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_FLOW_TABLE,
					MLX5_GET(query_flow_table_in, in,
						 table_id));
		break;
	case MLX5_CMD_OP_MODIFY_FLOW_TABLE:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_FLOW_TABLE,
					MLX5_GET(modify_flow_table_in, in,
						 table_id));
		break;
	case MLX5_CMD_OP_QUERY_FLOW_GROUP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_FLOW_GROUP,
					MLX5_GET(query_flow_group_in, in,
						 group_id));
		break;
	case MLX5_CMD_OP_QUERY_FLOW_TABLE_ENTRY:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY,
					MLX5_GET(query_fte_in, in,
						 flow_index));
		break;
	case MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_SET_FLOW_TABLE_ENTRY,
					MLX5_GET(set_fte_in, in, flow_index));
		break;
	case MLX5_CMD_OP_QUERY_Q_COUNTER:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_ALLOC_Q_COUNTER,
					MLX5_GET(query_q_counter_in, in,
						 counter_set_id));
		break;
	case MLX5_CMD_OP_QUERY_FLOW_COUNTER:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_ALLOC_FLOW_COUNTER,
					MLX5_GET(query_flow_counter_in, in,
						 flow_counter_id));
		break;
	case MLX5_CMD_OP_QUERY_MODIFY_HEADER_CONTEXT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT,
					MLX5_GET(general_obj_in_cmd_hdr, in,
						 obj_id));
		break;
	case MLX5_CMD_OP_QUERY_SCHEDULING_ELEMENT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT,
					MLX5_GET(query_scheduling_element_in,
						 in, scheduling_element_id));
		break;
	case MLX5_CMD_OP_MODIFY_SCHEDULING_ELEMENT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_SCHEDULING_ELEMENT,
					MLX5_GET(modify_scheduling_element_in,
						 in, scheduling_element_id));
		break;
	case MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT,
					MLX5_GET(add_vxlan_udp_dport_in, in,
						 vxlan_udp_port));
		break;
	case MLX5_CMD_OP_QUERY_L2_TABLE_ENTRY:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_SET_L2_TABLE_ENTRY,
					MLX5_GET(query_l2_table_entry_in, in,
						 table_index));
		break;
	case MLX5_CMD_OP_SET_L2_TABLE_ENTRY:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_SET_L2_TABLE_ENTRY,
					MLX5_GET(set_l2_table_entry_in, in,
						 table_index));
		break;
	case MLX5_CMD_OP_QUERY_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(query_qp_in, in, qpn));
		break;
	case MLX5_CMD_OP_RST2INIT_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(rst2init_qp_in, in, qpn));
		break;
	case MLX5_CMD_OP_INIT2RTR_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(init2rtr_qp_in, in, qpn));
		break;
	case MLX5_CMD_OP_RTR2RTS_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(rtr2rts_qp_in, in, qpn));
		break;
	case MLX5_CMD_OP_RTS2RTS_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(rts2rts_qp_in, in, qpn));
		break;
	case MLX5_CMD_OP_SQERR2RTS_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(sqerr2rts_qp_in, in, qpn));
		break;
	case MLX5_CMD_OP_2ERR_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(qp_2err_in, in, qpn));
		break;
	case MLX5_CMD_OP_2RST_QP:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_QP,
					MLX5_GET(qp_2rst_in, in, qpn));
		break;
	case MLX5_CMD_OP_QUERY_DCT:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_DCT,
					MLX5_GET(query_dct_in, in, dctn));
		break;
	case MLX5_CMD_OP_QUERY_XRQ:
	case MLX5_CMD_OP_QUERY_XRQ_DC_PARAMS_ENTRY:
	case MLX5_CMD_OP_QUERY_XRQ_ERROR_PARAMS:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_XRQ,
					MLX5_GET(query_xrq_in, in, xrqn));
		break;
	case MLX5_CMD_OP_QUERY_XRC_SRQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_XRC_SRQ,
					MLX5_GET(query_xrc_srq_in, in,
						 xrc_srqn));
		break;
	case MLX5_CMD_OP_ARM_XRC_SRQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_XRC_SRQ,
					MLX5_GET(arm_xrc_srq_in, in, xrc_srqn));
		break;
	case MLX5_CMD_OP_QUERY_SRQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_SRQ,
					MLX5_GET(query_srq_in, in, srqn));
		break;
	case MLX5_CMD_OP_ARM_RQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_RQ,
					MLX5_GET(arm_rq_in, in, srq_number));
		break;
	case MLX5_CMD_OP_ARM_DCT_FOR_KEY_VIOLATION:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_DCT,
					MLX5_GET(drain_dct_in, in, dctn));
		break;
	case MLX5_CMD_OP_ARM_XRQ:
	case MLX5_CMD_OP_SET_XRQ_DC_PARAMS_ENTRY:
	case MLX5_CMD_OP_RELEASE_XRQ_ERROR:
	case MLX5_CMD_OP_MODIFY_XRQ:
		obj_id = get_enc_obj_id(MLX5_CMD_OP_CREATE_XRQ,
					MLX5_GET(arm_xrq_in, in, xrqn));
		break;
	case MLX5_CMD_OP_QUERY_PACKET_REFORMAT_CONTEXT:
		obj_id = get_enc_obj_id
				(MLX5_CMD_OP_ALLOC_PACKET_REFORMAT_CONTEXT,
				 MLX5_GET(query_packet_reformat_context_in,
					  in, packet_reformat_id));
		break;
	default:
		obj_id = 0;
	}

	return obj_id;
}