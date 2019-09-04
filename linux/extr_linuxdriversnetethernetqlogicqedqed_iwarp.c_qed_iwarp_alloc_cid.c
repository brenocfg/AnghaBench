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
typedef  int /*<<< orphan*/  u32 ;
struct qed_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  lock; int /*<<< orphan*/  cid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  QED_ELEM_CXT ; 
 int qed_cxt_dynamic_ilt_alloc (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_cxt_get_proto_cid_start (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iwarp_cid_cleaned (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int qed_rdma_bmap_alloc_id (struct qed_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_iwarp_alloc_cid(struct qed_hwfn *p_hwfn, u32 *cid)
{
	int rc;

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn, &p_hwfn->p_rdma_info->cid_map, cid);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
	if (rc) {
		DP_NOTICE(p_hwfn, "Failed in allocating iwarp cid\n");
		return rc;
	}
	*cid += qed_cxt_get_proto_cid_start(p_hwfn, p_hwfn->p_rdma_info->proto);

	rc = qed_cxt_dynamic_ilt_alloc(p_hwfn, QED_ELEM_CXT, *cid);
	if (rc)
		qed_iwarp_cid_cleaned(p_hwfn, *cid);

	return rc;
}