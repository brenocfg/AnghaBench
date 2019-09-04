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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_vf_info {int /*<<< orphan*/  state; int /*<<< orphan*/  adapter; struct qlcnic_bc_trans* send_cmd; } ;
struct qlcnic_bc_trans {scalar_t__ trans_id; int curr_rsp_frag; int rsp_pay; int /*<<< orphan*/  resp_cmpl; TYPE_1__* rsp_hdr; int /*<<< orphan*/  rsp_pay_size; } ;
struct qlcnic_bc_hdr {scalar_t__ seq_id; } ;
struct TYPE_2__ {scalar_t__ num_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_BC_VF_SEND ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_get_bc_paysize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qlcnic_sriov_pull_bc_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_sriov_handle_bc_resp(struct qlcnic_bc_hdr *hdr,
					struct qlcnic_vf_info *vf)
{
	struct qlcnic_bc_trans *trans;
	u32 pay_size;

	if (test_and_set_bit(QLC_BC_VF_SEND, &vf->state))
		return;

	trans = vf->send_cmd;

	if (trans == NULL)
		goto clear_send;

	if (trans->trans_id != hdr->seq_id)
		goto clear_send;

	pay_size = qlcnic_sriov_get_bc_paysize(trans->rsp_pay_size,
					       trans->curr_rsp_frag);
	qlcnic_sriov_pull_bc_msg(vf->adapter,
				 (u32 *)(trans->rsp_hdr + trans->curr_rsp_frag),
				 (u32 *)(trans->rsp_pay + trans->curr_rsp_frag),
				 pay_size);
	if (++trans->curr_rsp_frag < trans->rsp_hdr->num_frags)
		goto clear_send;

	complete(&trans->resp_cmpl);

clear_send:
	clear_bit(QLC_BC_VF_SEND, &vf->state);
}