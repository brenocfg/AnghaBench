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
typedef  int /*<<< orphan*/  u16 ;
struct qed_qm_info {int /*<<< orphan*/  start_pq; int /*<<< orphan*/  first_vf_pq; int /*<<< orphan*/  first_llt_pq; int /*<<< orphan*/  first_ofld_pq; int /*<<< orphan*/  pure_ack_pq; int /*<<< orphan*/  ooo_pq; int /*<<< orphan*/  pure_lb_pq; int /*<<< orphan*/  first_mcos_pq; int /*<<< orphan*/  first_rl_pq; } ;
struct qed_hwfn {struct qed_qm_info qm_info; } ;
typedef  int /*<<< orphan*/  pq_flags ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,unsigned long) ; 
#define  PQ_FLAGS_ACK 135 
#define  PQ_FLAGS_LB 134 
#define  PQ_FLAGS_LLT 133 
#define  PQ_FLAGS_MCOS 132 
#define  PQ_FLAGS_OFLD 131 
#define  PQ_FLAGS_OOO 130 
#define  PQ_FLAGS_RLS 129 
#define  PQ_FLAGS_VFS 128 
 int bitmap_weight (unsigned long*,int) ; 
 unsigned long qed_get_pq_flags (struct qed_hwfn*) ; 

__attribute__((used)) static u16 *qed_init_qm_get_idx_from_flags(struct qed_hwfn *p_hwfn,
					   unsigned long pq_flags)
{
	struct qed_qm_info *qm_info = &p_hwfn->qm_info;

	/* Can't have multiple flags set here */
	if (bitmap_weight(&pq_flags,
			  sizeof(pq_flags) * BITS_PER_BYTE) > 1) {
		DP_ERR(p_hwfn, "requested multiple pq flags 0x%lx\n", pq_flags);
		goto err;
	}

	if (!(qed_get_pq_flags(p_hwfn) & pq_flags)) {
		DP_ERR(p_hwfn, "pq flag 0x%lx is not set\n", pq_flags);
		goto err;
	}

	switch (pq_flags) {
	case PQ_FLAGS_RLS:
		return &qm_info->first_rl_pq;
	case PQ_FLAGS_MCOS:
		return &qm_info->first_mcos_pq;
	case PQ_FLAGS_LB:
		return &qm_info->pure_lb_pq;
	case PQ_FLAGS_OOO:
		return &qm_info->ooo_pq;
	case PQ_FLAGS_ACK:
		return &qm_info->pure_ack_pq;
	case PQ_FLAGS_OFLD:
		return &qm_info->first_ofld_pq;
	case PQ_FLAGS_LLT:
		return &qm_info->first_llt_pq;
	case PQ_FLAGS_VFS:
		return &qm_info->first_vf_pq;
	default:
		goto err;
	}

err:
	return &qm_info->start_pq;
}