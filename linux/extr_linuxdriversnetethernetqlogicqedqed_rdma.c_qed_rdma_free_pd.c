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
typedef  int /*<<< orphan*/  u16 ;
struct qed_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pd_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  qed_bmap_release_id (struct qed_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qed_rdma_free_pd(void *rdma_cxt, u16 pd)
{
	struct qed_hwfn *p_hwfn = (struct qed_hwfn *)rdma_cxt;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "pd = %08x\n", pd);

	/* Returns a previously allocated protection domain for reuse */
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->pd_map, pd);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
}