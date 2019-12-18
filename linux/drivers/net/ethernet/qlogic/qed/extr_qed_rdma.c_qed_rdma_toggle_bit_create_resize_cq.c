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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  bitmap; } ;
struct qed_rdma_info {int /*<<< orphan*/  lock; TYPE_1__ toggle_bits; int /*<<< orphan*/  proto; } ;
struct qed_hwfn {struct qed_rdma_info* p_rdma_info; } ;
typedef  enum qed_rdma_toggle_bit { ____Placeholder_qed_rdma_toggle_bit } qed_rdma_toggle_bit ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int qed_cxt_get_proto_cid_start (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_change_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum qed_rdma_toggle_bit
qed_rdma_toggle_bit_create_resize_cq(struct qed_hwfn *p_hwfn, u16 icid)
{
	struct qed_rdma_info *p_info = p_hwfn->p_rdma_info;
	enum qed_rdma_toggle_bit toggle_bit;
	u32 bmap_id;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", icid);

	/* the function toggle the bit that is related to a given icid
	 * and returns the new toggle bit's value
	 */
	bmap_id = icid - qed_cxt_get_proto_cid_start(p_hwfn, p_info->proto);

	spin_lock_bh(&p_info->lock);
	toggle_bit = !test_and_change_bit(bmap_id,
					  p_info->toggle_bits.bitmap);
	spin_unlock_bh(&p_info->lock);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QED_RDMA_TOGGLE_BIT_= %d\n",
		   toggle_bit);

	return toggle_bit;
}