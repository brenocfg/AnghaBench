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
struct qed_iwarp_listener {int /*<<< orphan*/  list_entry; } ;
struct qed_hwfn {TYPE_2__* p_rdma_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  iw_lock; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  kfree (struct qed_iwarp_listener*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int qed_iwarp_destroy_listen(void *rdma_cxt, void *handle)
{
	struct qed_iwarp_listener *listener = handle;
	struct qed_hwfn *p_hwfn = rdma_cxt;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "handle=%p\n", handle);

	spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	list_del(&listener->list_entry);
	spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	kfree(listener);

	return 0;
}