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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct qlcnic_vf_info {int /*<<< orphan*/  adapter; } ;
struct qlcnic_bc_trans {scalar_t__ func_id; scalar_t__ curr_rsp_frag; int /*<<< orphan*/  rsp_pay_size; scalar_t__ rsp_pay; scalar_t__ rsp_hdr; scalar_t__ curr_req_frag; int /*<<< orphan*/  req_pay_size; scalar_t__ req_pay; scalar_t__ req_hdr; struct qlcnic_vf_info* vf; } ;
struct qlcnic_bc_hdr {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ QLC_BC_COMMAND ; 
 scalar_t__ __qlcnic_sriov_issue_bc_post (struct qlcnic_vf_info*) ; 
 int qlcnic_sriov_get_bc_paysize (int /*<<< orphan*/ ,scalar_t__) ; 
 int qlcnic_sriov_post_bc_msg (int /*<<< orphan*/ ,int*,int*,scalar_t__,int) ; 

__attribute__((used)) static int qlcnic_sriov_issue_bc_post(struct qlcnic_bc_trans *trans, u8 type)
{
	struct qlcnic_vf_info *vf = trans->vf;
	u32 pay_size, hdr_size;
	u32 *hdr, *pay;
	int ret;
	u8 pci_func = trans->func_id;

	if (__qlcnic_sriov_issue_bc_post(vf))
		return -EBUSY;

	if (type == QLC_BC_COMMAND) {
		hdr = (u32 *)(trans->req_hdr + trans->curr_req_frag);
		pay = (u32 *)(trans->req_pay + trans->curr_req_frag);
		hdr_size = (sizeof(struct qlcnic_bc_hdr) / sizeof(u32));
		pay_size = qlcnic_sriov_get_bc_paysize(trans->req_pay_size,
						       trans->curr_req_frag);
		pay_size = (pay_size / sizeof(u32));
	} else {
		hdr = (u32 *)(trans->rsp_hdr + trans->curr_rsp_frag);
		pay = (u32 *)(trans->rsp_pay + trans->curr_rsp_frag);
		hdr_size = (sizeof(struct qlcnic_bc_hdr) / sizeof(u32));
		pay_size = qlcnic_sriov_get_bc_paysize(trans->rsp_pay_size,
						       trans->curr_rsp_frag);
		pay_size = (pay_size / sizeof(u32));
	}

	ret = qlcnic_sriov_post_bc_msg(vf->adapter, hdr, pay,
				       pci_func, pay_size);
	return ret;
}