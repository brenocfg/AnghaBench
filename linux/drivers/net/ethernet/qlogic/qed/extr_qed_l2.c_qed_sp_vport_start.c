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
struct qed_sp_vport_start_params {int /*<<< orphan*/  only_untagged; int /*<<< orphan*/  max_buffers_per_cqe; int /*<<< orphan*/  tpa_mode; int /*<<< orphan*/  remove_inner_vlan; int /*<<< orphan*/  mtu; int /*<<< orphan*/  vport_id; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int qed_sp_eth_vport_start (struct qed_hwfn*,struct qed_sp_vport_start_params*) ; 
 int qed_vf_pf_vport_start (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_sp_vport_start(struct qed_hwfn *p_hwfn,
			      struct qed_sp_vport_start_params *p_params)
{
	if (IS_VF(p_hwfn->cdev)) {
		return qed_vf_pf_vport_start(p_hwfn, p_params->vport_id,
					     p_params->mtu,
					     p_params->remove_inner_vlan,
					     p_params->tpa_mode,
					     p_params->max_buffers_per_cqe,
					     p_params->only_untagged);
	}

	return qed_sp_eth_vport_start(p_hwfn, p_params);
}