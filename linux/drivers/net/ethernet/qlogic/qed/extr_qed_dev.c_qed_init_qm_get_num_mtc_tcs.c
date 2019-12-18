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
typedef  int u8 ;
typedef  int u32 ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int PQ_FLAGS_MTC ; 
 int qed_get_pq_flags (struct qed_hwfn*) ; 
 int qed_init_qm_get_num_tcs (struct qed_hwfn*) ; 

__attribute__((used)) static u8 qed_init_qm_get_num_mtc_tcs(struct qed_hwfn *p_hwfn)
{
	u32 pq_flags = qed_get_pq_flags(p_hwfn);

	if (!(PQ_FLAGS_MTC & pq_flags))
		return 1;

	return qed_init_qm_get_num_tcs(p_hwfn);
}