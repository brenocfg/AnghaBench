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
typedef  int u32 ;
struct qed_iscsi_pf_params {int num_cons; int /*<<< orphan*/  num_tasks; } ;
struct qed_fcoe_pf_params {int num_cons; int /*<<< orphan*/  num_tasks; } ;
struct qed_eth_pf_params {int num_cons; int /*<<< orphan*/  num_arfs_filters; int /*<<< orphan*/  num_vf_cons; } ;
struct TYPE_6__ {struct qed_iscsi_pf_params iscsi_pf_params; struct qed_fcoe_pf_params fcoe_pf_params; struct qed_eth_pf_params eth_pf_params; int /*<<< orphan*/  rdma_pf_params; } ;
struct TYPE_4__ {int personality; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; TYPE_3__ pf_params; TYPE_2__* p_cxt_mngr; TYPE_1__ hw_info; scalar_t__ using_ll2; } ;
struct TYPE_5__ {int /*<<< orphan*/  arfs_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_PF_PARAMS_VF_CONS_DEFAULT ; 
 int /*<<< orphan*/  PROTOCOLID_CORE ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int /*<<< orphan*/  PROTOCOLID_FCOE ; 
 int /*<<< orphan*/  PROTOCOLID_ISCSI ; 
 int /*<<< orphan*/  QED_CXT_FCOE_TID_SEG ; 
 int /*<<< orphan*/  QED_CXT_ISCSI_TID_SEG ; 
#define  QED_PCI_ETH 133 
#define  QED_PCI_ETH_IWARP 132 
#define  QED_PCI_ETH_RDMA 131 
#define  QED_PCI_ETH_ROCE 130 
#define  QED_PCI_FCOE 129 
#define  QED_PCI_ISCSI 128 
 int /*<<< orphan*/  qed_cxt_set_proto_cid_count (struct qed_hwfn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_cxt_set_proto_tid_count (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_rdma_set_pf_params (struct qed_hwfn*,int /*<<< orphan*/ *,int) ; 

int qed_cxt_set_pf_params(struct qed_hwfn *p_hwfn, u32 rdma_tasks)
{
	/* Set the number of required CORE connections */
	u32 core_cids = 1; /* SPQ */

	if (p_hwfn->using_ll2)
		core_cids += 4;
	qed_cxt_set_proto_cid_count(p_hwfn, PROTOCOLID_CORE, core_cids, 0);

	switch (p_hwfn->hw_info.personality) {
	case QED_PCI_ETH_RDMA:
	case QED_PCI_ETH_IWARP:
	case QED_PCI_ETH_ROCE:
	{
			qed_rdma_set_pf_params(p_hwfn,
					       &p_hwfn->
					       pf_params.rdma_pf_params,
					       rdma_tasks);
		/* no need for break since RoCE coexist with Ethernet */
	}
	/* fall through */
	case QED_PCI_ETH:
	{
		struct qed_eth_pf_params *p_params =
		    &p_hwfn->pf_params.eth_pf_params;

		if (!p_params->num_vf_cons)
			p_params->num_vf_cons =
			    ETH_PF_PARAMS_VF_CONS_DEFAULT;
		qed_cxt_set_proto_cid_count(p_hwfn, PROTOCOLID_ETH,
					    p_params->num_cons,
					    p_params->num_vf_cons);
		p_hwfn->p_cxt_mngr->arfs_count = p_params->num_arfs_filters;
		break;
	}
	case QED_PCI_FCOE:
	{
		struct qed_fcoe_pf_params *p_params;

		p_params = &p_hwfn->pf_params.fcoe_pf_params;

		if (p_params->num_cons && p_params->num_tasks) {
			qed_cxt_set_proto_cid_count(p_hwfn,
						    PROTOCOLID_FCOE,
						    p_params->num_cons,
						    0);

			qed_cxt_set_proto_tid_count(p_hwfn, PROTOCOLID_FCOE,
						    QED_CXT_FCOE_TID_SEG, 0,
						    p_params->num_tasks, true);
		} else {
			DP_INFO(p_hwfn->cdev,
				"Fcoe personality used without setting params!\n");
		}
		break;
	}
	case QED_PCI_ISCSI:
	{
		struct qed_iscsi_pf_params *p_params;

		p_params = &p_hwfn->pf_params.iscsi_pf_params;

		if (p_params->num_cons && p_params->num_tasks) {
			qed_cxt_set_proto_cid_count(p_hwfn,
						    PROTOCOLID_ISCSI,
						    p_params->num_cons,
						    0);

			qed_cxt_set_proto_tid_count(p_hwfn,
						    PROTOCOLID_ISCSI,
						    QED_CXT_ISCSI_TID_SEG,
						    0,
						    p_params->num_tasks,
						    true);
		} else {
			DP_INFO(p_hwfn->cdev,
				"Iscsi personality used without setting params!\n");
		}
		break;
	}
	default:
		return -EINVAL;
	}

	return 0;
}