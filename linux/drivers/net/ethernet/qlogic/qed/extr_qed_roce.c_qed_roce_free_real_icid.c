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
struct qed_rdma_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  cid_map; int /*<<< orphan*/  real_cid_map; int /*<<< orphan*/  proto; } ;
struct qed_hwfn {struct qed_rdma_info* p_rdma_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_bmap_release_id (struct qed_hwfn*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ qed_bmap_test_id (struct qed_hwfn*,int /*<<< orphan*/ *,int) ; 
 int qed_cxt_get_proto_cid_start (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qed_roce_free_real_icid(struct qed_hwfn *p_hwfn, u16 icid)
{
	struct qed_rdma_info *p_rdma_info = p_hwfn->p_rdma_info;
	u32 start_cid, cid, xcid;

	/* an even icid belongs to a responder while an odd icid belongs to a
	 * requester. The 'cid' received as an input can be either. We calculate
	 * the "partner" icid and call it xcid. Only if both are free then the
	 * "cid" map can be cleared.
	 */
	start_cid = qed_cxt_get_proto_cid_start(p_hwfn, p_rdma_info->proto);
	cid = icid - start_cid;
	xcid = cid ^ 1;

	spin_lock_bh(&p_rdma_info->lock);

	qed_bmap_release_id(p_hwfn, &p_rdma_info->real_cid_map, cid);
	if (qed_bmap_test_id(p_hwfn, &p_rdma_info->real_cid_map, xcid) == 0) {
		qed_bmap_release_id(p_hwfn, &p_rdma_info->cid_map, cid);
		qed_bmap_release_id(p_hwfn, &p_rdma_info->cid_map, xcid);
	}

	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
}