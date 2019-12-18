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
struct qed_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  cid_map; int /*<<< orphan*/  tcp_cid_map; } ;

/* Variables and functions */
 int QED_IWARP_PREALLOC_CNT ; 
 int /*<<< orphan*/  qed_bmap_release_id (struct qed_hwfn*,int /*<<< orphan*/ *,int) ; 
 int qed_iwarp_wait_cid_map_cleared (struct qed_hwfn*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_iwarp_wait_for_all_cids(struct qed_hwfn *p_hwfn)
{
	int rc;
	int i;

	rc = qed_iwarp_wait_cid_map_cleared(p_hwfn,
					    &p_hwfn->p_rdma_info->tcp_cid_map);
	if (rc)
		return rc;

	/* Now free the tcp cids from the main cid map */
	for (i = 0; i < QED_IWARP_PREALLOC_CNT; i++)
		qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->cid_map, i);

	/* Now wait for all cids to be completed */
	return qed_iwarp_wait_cid_map_cleared(p_hwfn,
					      &p_hwfn->p_rdma_info->cid_map);
}