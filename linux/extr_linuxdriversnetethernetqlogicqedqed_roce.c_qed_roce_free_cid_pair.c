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
typedef  scalar_t__ u16 ;
struct qed_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_bmap_release_id (struct qed_hwfn*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qed_roce_free_cid_pair(struct qed_hwfn *p_hwfn, u16 cid)
{
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->cid_map, cid);
	qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->cid_map, cid + 1);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
}