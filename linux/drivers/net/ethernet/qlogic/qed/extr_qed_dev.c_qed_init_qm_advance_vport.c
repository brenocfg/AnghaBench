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
struct qed_qm_info {scalar_t__ num_vports; } ;
struct qed_hwfn {struct qed_qm_info qm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ qed_init_qm_get_num_vports (struct qed_hwfn*) ; 

__attribute__((used)) static void qed_init_qm_advance_vport(struct qed_hwfn *p_hwfn)
{
	struct qed_qm_info *qm_info = &p_hwfn->qm_info;

	qm_info->num_vports++;

	if (qm_info->num_vports > qed_init_qm_get_num_vports(p_hwfn))
		DP_ERR(p_hwfn,
		       "vport overflow! qm_info->num_vports %d, qm_init_get_num_vports() %d\n",
		       qm_info->num_vports, qed_init_qm_get_num_vports(p_hwfn));
}