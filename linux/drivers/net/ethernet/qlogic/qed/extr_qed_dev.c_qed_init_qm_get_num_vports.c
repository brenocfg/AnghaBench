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
typedef  int u32 ;
typedef  int u16 ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int PQ_FLAGS_RLS ; 
 int PQ_FLAGS_VFS ; 
 int qed_get_pq_flags (struct qed_hwfn*) ; 
 int qed_init_qm_get_num_pf_rls (struct qed_hwfn*) ; 
 int qed_init_qm_get_num_vfs (struct qed_hwfn*) ; 

__attribute__((used)) static u16 qed_init_qm_get_num_vports(struct qed_hwfn *p_hwfn)
{
	u32 pq_flags = qed_get_pq_flags(p_hwfn);

	/* all pqs share the same vport, except for vfs and pf_rl pqs */
	return (!!(PQ_FLAGS_RLS & pq_flags)) *
	       qed_init_qm_get_num_pf_rls(p_hwfn) +
	       (!!(PQ_FLAGS_VFS & pq_flags)) *
	       qed_init_qm_get_num_vfs(p_hwfn) + 1;
}