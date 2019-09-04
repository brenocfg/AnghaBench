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
struct qed_ptt {int dummy; } ;
struct TYPE_2__ {int num_vports; struct init_qm_vport_params* qm_vport_params; } ;
struct qed_hwfn {TYPE_1__ qm_info; } ;
struct init_qm_vport_params {int /*<<< orphan*/  vport_wfq; int /*<<< orphan*/  first_tx_pq_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_init_vport_wfq (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_init_wfq_default_param (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_disable_wfq_for_all_vports(struct qed_hwfn *p_hwfn,
					   struct qed_ptt *p_ptt,
					   u32 min_pf_rate)
{
	struct init_qm_vport_params *vport_params;
	int i;

	vport_params = p_hwfn->qm_info.qm_vport_params;

	for (i = 0; i < p_hwfn->qm_info.num_vports; i++) {
		qed_init_wfq_default_param(p_hwfn, min_pf_rate);
		qed_init_vport_wfq(p_hwfn, p_ptt,
				   vport_params[i].first_tx_pq_id,
				   vport_params[i].vport_wfq);
	}
}