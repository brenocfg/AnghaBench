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

/* Variables and functions */
 int QM_OTHER_PQS_PER_PF ; 
 int QM_PQ_MEM_4KB (int) ; 

u32 qed_qm_pf_mem_size(u32 num_pf_cids,
		       u32 num_vf_cids,
		       u32 num_tids, u16 num_pf_pqs, u16 num_vf_pqs)
{
	return QM_PQ_MEM_4KB(num_pf_cids) * num_pf_pqs +
	       QM_PQ_MEM_4KB(num_vf_cids) * num_vf_pqs +
	       QM_PQ_MEM_4KB(num_pf_cids + num_tids) * QM_OTHER_PQS_PER_PF;
}