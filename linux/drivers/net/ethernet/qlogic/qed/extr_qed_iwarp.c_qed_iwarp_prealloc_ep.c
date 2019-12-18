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
typedef  int /*<<< orphan*/  u32 ;
struct qed_iwarp_ep {int /*<<< orphan*/  list_entry; int /*<<< orphan*/  tcp_cid; } ;
struct qed_hwfn {TYPE_2__* p_rdma_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  iw_lock; int /*<<< orphan*/  ep_free_list; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int QED_IWARP_PREALLOC_CNT ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int qed_iwarp_alloc_cid (struct qed_hwfn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_iwarp_alloc_tcp_cid (struct qed_hwfn*,int /*<<< orphan*/ *) ; 
 int qed_iwarp_create_ep (struct qed_hwfn*,struct qed_iwarp_ep**) ; 
 int /*<<< orphan*/  qed_iwarp_destroy_ep (struct qed_hwfn*,struct qed_iwarp_ep*,int) ; 
 int /*<<< orphan*/  qed_iwarp_set_tcp_cid (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_iwarp_prealloc_ep(struct qed_hwfn *p_hwfn, bool init)
{
	struct qed_iwarp_ep *ep;
	int rc = 0;
	int count;
	u32 cid;
	int i;

	count = init ? QED_IWARP_PREALLOC_CNT : 1;
	for (i = 0; i < count; i++) {
		rc = qed_iwarp_create_ep(p_hwfn, &ep);
		if (rc)
			return rc;

		/* During initialization we allocate from the main pool,
		 * afterwards we allocate only from the tcp_cid.
		 */
		if (init) {
			rc = qed_iwarp_alloc_cid(p_hwfn, &cid);
			if (rc)
				goto err;
			qed_iwarp_set_tcp_cid(p_hwfn, cid);
		} else {
			/* We don't care about the return code, it's ok if
			 * tcp_cid remains invalid...in this case we'll
			 * defer allocation
			 */
			qed_iwarp_alloc_tcp_cid(p_hwfn, &cid);
		}

		ep->tcp_cid = cid;

		spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
		list_add_tail(&ep->list_entry,
			      &p_hwfn->p_rdma_info->iwarp.ep_free_list);
		spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	}

	return rc;

err:
	qed_iwarp_destroy_ep(p_hwfn, ep, false);

	return rc;
}