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
struct TYPE_4__ {int /*<<< orphan*/  iw_lock; int /*<<< orphan*/  ep_free_list; } ;
struct TYPE_3__ {TYPE_2__ iwarp; int /*<<< orphan*/  tcp_cid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QED_IWARP_PREALLOC_CNT ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int qed_iwarp_prealloc_ep (struct qed_hwfn*,int) ; 
 int qed_ooo_alloc (struct qed_hwfn*) ; 
 int qed_rdma_bmap_alloc (struct qed_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int qed_iwarp_alloc(struct qed_hwfn *p_hwfn)
{
	int rc;

	/* Allocate bitmap for tcp cid. These are used by passive side
	 * to ensure it can allocate a tcp cid during dpc that was
	 * pre-acquired and doesn't require dynamic allocation of ilt
	 */
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_hwfn->p_rdma_info->tcp_cid_map,
				 QED_IWARP_PREALLOC_CNT, "TCP_CID");
	if (rc) {
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate tcp cid, rc = %d\n", rc);
		return rc;
	}

	INIT_LIST_HEAD(&p_hwfn->p_rdma_info->iwarp.ep_free_list);
	spin_lock_init(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	rc = qed_iwarp_prealloc_ep(p_hwfn, true);
	if (rc)
		return rc;

	return qed_ooo_alloc(p_hwfn);
}