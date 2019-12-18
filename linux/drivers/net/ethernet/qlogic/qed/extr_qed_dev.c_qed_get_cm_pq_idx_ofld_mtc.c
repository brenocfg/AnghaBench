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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQ_FLAGS_OFLD ; 
 scalar_t__ PQ_INIT_DEFAULT_TC ; 
 scalar_t__ qed_get_cm_pq_idx (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_init_qm_get_num_mtc_tcs (struct qed_hwfn*) ; 

u16 qed_get_cm_pq_idx_ofld_mtc(struct qed_hwfn *p_hwfn, u8 tc)
{
	u16 first_ofld_pq, pq_offset;

	first_ofld_pq = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	pq_offset = (tc < qed_init_qm_get_num_mtc_tcs(p_hwfn)) ?
		    tc : PQ_INIT_DEFAULT_TC;

	return first_ofld_pq + pq_offset;
}