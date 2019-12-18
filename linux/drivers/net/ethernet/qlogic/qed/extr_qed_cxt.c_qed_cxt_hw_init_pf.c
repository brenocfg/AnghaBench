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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_cdu_init_pf (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_cm_init_pf (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_dq_init_pf (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ilt_init_pf (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_prs_init_pf (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_qm_init_pf (struct qed_hwfn*,struct qed_ptt*,int) ; 
 int /*<<< orphan*/  qed_src_init_pf (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_tm_init_pf (struct qed_hwfn*) ; 

void qed_cxt_hw_init_pf(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	qed_qm_init_pf(p_hwfn, p_ptt, true);
	qed_cm_init_pf(p_hwfn);
	qed_dq_init_pf(p_hwfn);
	qed_cdu_init_pf(p_hwfn);
	qed_ilt_init_pf(p_hwfn);
	qed_src_init_pf(p_hwfn);
	qed_tm_init_pf(p_hwfn);
	qed_prs_init_pf(p_hwfn);
}