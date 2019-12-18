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
struct TYPE_2__ {scalar_t__ multi_tc_roce_en; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int EINVAL ; 
 scalar_t__ QED_IS_ROCE_PERSONALITY (struct qed_hwfn*) ; 
 int /*<<< orphan*/  QED_PQ ; 
 int /*<<< orphan*/  QED_VPORT ; 
 scalar_t__ RESC_NUM (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_init_qm_get_num_pqs (struct qed_hwfn*) ; 
 scalar_t__ qed_init_qm_get_num_vports (struct qed_hwfn*) ; 

__attribute__((used)) static int qed_init_qm_sanity(struct qed_hwfn *p_hwfn)
{
	if (qed_init_qm_get_num_vports(p_hwfn) > RESC_NUM(p_hwfn, QED_VPORT)) {
		DP_ERR(p_hwfn, "requested amount of vports exceeds resource\n");
		return -EINVAL;
	}

	if (qed_init_qm_get_num_pqs(p_hwfn) <= RESC_NUM(p_hwfn, QED_PQ))
		return 0;

	if (QED_IS_ROCE_PERSONALITY(p_hwfn)) {
		p_hwfn->hw_info.multi_tc_roce_en = 0;
		DP_NOTICE(p_hwfn,
			  "multi-tc roce was disabled to reduce requested amount of pqs\n");
		if (qed_init_qm_get_num_pqs(p_hwfn) <= RESC_NUM(p_hwfn, QED_PQ))
			return 0;
	}

	DP_ERR(p_hwfn, "requested amount of pqs exceeds resource\n");
	return -EINVAL;
}