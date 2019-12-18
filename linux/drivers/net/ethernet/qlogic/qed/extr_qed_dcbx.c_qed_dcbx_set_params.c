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
typedef  int u8 ;
struct qed_ptt {int dummy; } ;
struct TYPE_6__ {int personality; } ;
struct qed_hwfn {TYPE_2__* cdev; TYPE_3__ hw_info; } ;
struct qed_dcbx_results {TYPE_1__* arr; } ;
typedef  enum qed_pci_personality { ____Placeholder_qed_pci_personality } qed_pci_personality ;
typedef  enum dcbx_protocol_type { ____Placeholder_dcbx_protocol_type } dcbx_protocol_type ;
struct TYPE_5__ {int /*<<< orphan*/  mf_bits; } ;
struct TYPE_4__ {int enable; int priority; int tc; int dont_add_vlan0; int /*<<< orphan*/  update; } ;

/* Variables and functions */
 int DCBX_PROTOCOL_ROCE ; 
 int /*<<< orphan*/  DONT_UPDATE_DCB_DSCP ; 
 int /*<<< orphan*/  DORQ_REG_PF_PCP_BB_K2 ; 
 int /*<<< orphan*/  DORQ_REG_TAG1_OVRD_MODE ; 
 int /*<<< orphan*/  QED_MF_DONT_ADD_VLAN0_TAG ; 
 int /*<<< orphan*/  QED_MF_UFP_SPECIFIC ; 
 int /*<<< orphan*/  UPDATE_DCB ; 
 int /*<<< orphan*/  qed_hw_info_set_offload_tc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qed_dcbx_set_params(struct qed_dcbx_results *p_data,
		    struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt,
		    bool app_tlv, bool enable, u8 prio, u8 tc,
		    enum dcbx_protocol_type type,
		    enum qed_pci_personality personality)
{
	/* PF update ramrod data */
	p_data->arr[type].enable = enable;
	p_data->arr[type].priority = prio;
	p_data->arr[type].tc = tc;
	if (enable)
		p_data->arr[type].update = UPDATE_DCB;
	else
		p_data->arr[type].update = DONT_UPDATE_DCB_DSCP;

	if (test_bit(QED_MF_DONT_ADD_VLAN0_TAG, &p_hwfn->cdev->mf_bits))
		p_data->arr[type].dont_add_vlan0 = true;

	/* QM reconf data */
	if (app_tlv && p_hwfn->hw_info.personality == personality)
		qed_hw_info_set_offload_tc(&p_hwfn->hw_info, tc);

	/* Configure dcbx vlan priority in doorbell block for roce EDPM */
	if (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits) &&
	    type == DCBX_PROTOCOL_ROCE) {
		qed_wr(p_hwfn, p_ptt, DORQ_REG_TAG1_OVRD_MODE, 1);
		qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_PCP_BB_K2, prio << 1);
	}
}