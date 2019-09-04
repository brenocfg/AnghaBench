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
struct qed_iwarp_info {int /*<<< orphan*/  mpa_intermediate_buf; int /*<<< orphan*/  partial_fpdus; int /*<<< orphan*/  mpa_bufs; } ;
struct qed_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_cid_map; struct qed_iwarp_info iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ooo_free (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_rdma_bmap_free (struct qed_hwfn*,int /*<<< orphan*/ *,int) ; 

void qed_iwarp_resc_free(struct qed_hwfn *p_hwfn)
{
	struct qed_iwarp_info *iwarp_info = &p_hwfn->p_rdma_info->iwarp;

	qed_ooo_free(p_hwfn);
	qed_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->tcp_cid_map, 1);
	kfree(iwarp_info->mpa_bufs);
	kfree(iwarp_info->partial_fpdus);
	kfree(iwarp_info->mpa_intermediate_buf);
}