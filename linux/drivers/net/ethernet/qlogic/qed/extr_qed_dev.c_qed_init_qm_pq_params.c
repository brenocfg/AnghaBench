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
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_init_qm_advance_vport (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_init_qm_lb_pq (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_init_qm_low_latency_pq (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_init_qm_mcos_pqs (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_init_qm_offload_pq (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_init_qm_ooo_pq (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_init_qm_pure_ack_pq (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_init_qm_rl_pqs (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_init_qm_vf_pqs (struct qed_hwfn*) ; 

__attribute__((used)) static void qed_init_qm_pq_params(struct qed_hwfn *p_hwfn)
{
	/* rate limited pqs, must come first (FW assumption) */
	qed_init_qm_rl_pqs(p_hwfn);

	/* pqs for multi cos */
	qed_init_qm_mcos_pqs(p_hwfn);

	/* pure loopback pq */
	qed_init_qm_lb_pq(p_hwfn);

	/* out of order pq */
	qed_init_qm_ooo_pq(p_hwfn);

	/* pure ack pq */
	qed_init_qm_pure_ack_pq(p_hwfn);

	/* pq for offloaded protocol */
	qed_init_qm_offload_pq(p_hwfn);

	/* low latency pq */
	qed_init_qm_low_latency_pq(p_hwfn);

	/* done sharing vports */
	qed_init_qm_advance_vport(p_hwfn);

	/* pqs for vfs */
	qed_init_qm_vf_pqs(p_hwfn);
}