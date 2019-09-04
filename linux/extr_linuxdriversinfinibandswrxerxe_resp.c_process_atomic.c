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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ atomic_orig; struct rxe_mem* mr; } ;
struct rxe_qp {TYPE_1__ resp; } ;
struct rxe_pkt_info {scalar_t__ opcode; } ;
struct rxe_mem {scalar_t__ state; } ;
typedef  enum resp_states { ____Placeholder_resp_states } resp_states ;

/* Variables and functions */
 scalar_t__ IB_OPCODE_RC_COMPARE_SWAP ; 
 scalar_t__ IB_OPCODE_RD_COMPARE_SWAP ; 
 int RESPST_ERR_MISALIGNED_ATOMIC ; 
 int RESPST_ERR_RKEY_VIOLATION ; 
 int RESPST_NONE ; 
 scalar_t__ RXE_MEM_STATE_VALID ; 
 scalar_t__ atmeth_comp (struct rxe_pkt_info*) ; 
 scalar_t__ atmeth_swap_add (struct rxe_pkt_info*) ; 
 scalar_t__ atmeth_va (struct rxe_pkt_info*) ; 
 int /*<<< orphan*/  atomic_ops_lock ; 
 scalar_t__* iova_to_vaddr (struct rxe_mem*,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum resp_states process_atomic(struct rxe_qp *qp,
				       struct rxe_pkt_info *pkt)
{
	u64 iova = atmeth_va(pkt);
	u64 *vaddr;
	enum resp_states ret;
	struct rxe_mem *mr = qp->resp.mr;

	if (mr->state != RXE_MEM_STATE_VALID) {
		ret = RESPST_ERR_RKEY_VIOLATION;
		goto out;
	}

	vaddr = iova_to_vaddr(mr, iova, sizeof(u64));

	/* check vaddr is 8 bytes aligned. */
	if (!vaddr || (uintptr_t)vaddr & 7) {
		ret = RESPST_ERR_MISALIGNED_ATOMIC;
		goto out;
	}

	spin_lock_bh(&atomic_ops_lock);

	qp->resp.atomic_orig = *vaddr;

	if (pkt->opcode == IB_OPCODE_RC_COMPARE_SWAP ||
	    pkt->opcode == IB_OPCODE_RD_COMPARE_SWAP) {
		if (*vaddr == atmeth_comp(pkt))
			*vaddr = atmeth_swap_add(pkt);
	} else {
		*vaddr += atmeth_swap_add(pkt);
	}

	spin_unlock_bh(&atomic_ops_lock);

	ret = RESPST_NONE;
out:
	return ret;
}