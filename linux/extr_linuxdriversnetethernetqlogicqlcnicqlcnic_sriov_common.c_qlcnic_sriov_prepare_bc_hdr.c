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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int* arg; int num; } ;
struct TYPE_3__ {int* arg; int num; } ;
struct qlcnic_cmd_args {int /*<<< orphan*/  op_type; TYPE_2__ rsp; TYPE_1__ req; scalar_t__ cmd_op; } ;
struct qlcnic_bc_trans {int req_pay_size; int rsp_pay_size; int trans_id; scalar_t__ cmd_id; struct qlcnic_bc_hdr* req_hdr; struct qlcnic_bc_hdr* rsp_hdr; struct qlcnic_bc_payload* rsp_pay; struct qlcnic_bc_payload* req_pay; } ;
struct qlcnic_bc_payload {int dummy; } ;
struct qlcnic_bc_hdr {int version; int num_cmds; int frag_num; int seq_id; scalar_t__ cmd_op; scalar_t__ num_frags; int /*<<< orphan*/  op_type; scalar_t__ msg_type; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ QLC_BC_COMMAND ; 
 int QLC_BC_PAYLOAD_SZ ; 
 scalar_t__ qlcnic_sriov_alloc_bc_msg (struct qlcnic_bc_hdr**,scalar_t__) ; 

__attribute__((used)) static int qlcnic_sriov_prepare_bc_hdr(struct qlcnic_bc_trans *trans,
				       struct qlcnic_cmd_args *cmd,
				       u16 seq, u8 msg_type)
{
	struct qlcnic_bc_hdr *hdr;
	int i;
	u32 num_regs, bc_pay_sz;
	u16 remainder;
	u8 cmd_op, num_frags, t_num_frags;

	bc_pay_sz = QLC_BC_PAYLOAD_SZ;
	if (msg_type == QLC_BC_COMMAND) {
		trans->req_pay = (struct qlcnic_bc_payload *)cmd->req.arg;
		trans->rsp_pay = (struct qlcnic_bc_payload *)cmd->rsp.arg;
		num_regs = cmd->req.num;
		trans->req_pay_size = (num_regs * 4);
		num_regs = cmd->rsp.num;
		trans->rsp_pay_size = (num_regs * 4);
		cmd_op = cmd->req.arg[0] & 0xff;
		remainder = (trans->req_pay_size) % (bc_pay_sz);
		num_frags = (trans->req_pay_size) / (bc_pay_sz);
		if (remainder)
			num_frags++;
		t_num_frags = num_frags;
		if (qlcnic_sriov_alloc_bc_msg(&trans->req_hdr, num_frags))
			return -ENOMEM;
		remainder = (trans->rsp_pay_size) % (bc_pay_sz);
		num_frags = (trans->rsp_pay_size) / (bc_pay_sz);
		if (remainder)
			num_frags++;
		if (qlcnic_sriov_alloc_bc_msg(&trans->rsp_hdr, num_frags))
			return -ENOMEM;
		num_frags  = t_num_frags;
		hdr = trans->req_hdr;
	}  else {
		cmd->req.arg = (u32 *)trans->req_pay;
		cmd->rsp.arg = (u32 *)trans->rsp_pay;
		cmd_op = cmd->req.arg[0] & 0xff;
		cmd->cmd_op = cmd_op;
		remainder = (trans->rsp_pay_size) % (bc_pay_sz);
		num_frags = (trans->rsp_pay_size) / (bc_pay_sz);
		if (remainder)
			num_frags++;
		cmd->req.num = trans->req_pay_size / 4;
		cmd->rsp.num = trans->rsp_pay_size / 4;
		hdr = trans->rsp_hdr;
		cmd->op_type = trans->req_hdr->op_type;
	}

	trans->trans_id = seq;
	trans->cmd_id = cmd_op;
	for (i = 0; i < num_frags; i++) {
		hdr[i].version = 2;
		hdr[i].msg_type = msg_type;
		hdr[i].op_type = cmd->op_type;
		hdr[i].num_cmds = 1;
		hdr[i].num_frags = num_frags;
		hdr[i].frag_num = i + 1;
		hdr[i].cmd_op = cmd_op;
		hdr[i].seq_id = seq;
	}
	return 0;
}