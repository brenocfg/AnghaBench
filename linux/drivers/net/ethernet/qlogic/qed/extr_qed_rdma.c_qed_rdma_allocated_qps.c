#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qed_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  bitmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; TYPE_2__ cid_map; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_bmap_is_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

bool qed_rdma_allocated_qps(struct qed_hwfn *p_hwfn)
{
	bool result;

	/* if rdma wasn't activated yet, naturally there are no qps */
	if (!p_hwfn->p_rdma_info->active)
		return false;

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	if (!p_hwfn->p_rdma_info->cid_map.bitmap)
		result = false;
	else
		result = !qed_bmap_is_empty(&p_hwfn->p_rdma_info->cid_map);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
	return result;
}