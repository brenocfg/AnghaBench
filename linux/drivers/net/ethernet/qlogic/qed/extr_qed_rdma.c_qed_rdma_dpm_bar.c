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
struct qed_hwfn {int db_bar_no_edpm; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_rdma_dpm_conf (struct qed_hwfn*,struct qed_ptt*) ; 

void qed_rdma_dpm_bar(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	p_hwfn->db_bar_no_edpm = true;

	qed_rdma_dpm_conf(p_hwfn, p_ptt);
}