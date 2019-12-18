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
struct iwl_rb_allocator {int /*<<< orphan*/  rx_alloc; int /*<<< orphan*/  alloc_wq; int /*<<< orphan*/  req_pending; } ;
struct iwl_trans_pcie {struct iwl_rb_allocator rba; } ;
struct iwl_trans {int dummy; } ;
struct iwl_rxq {int used_count; int /*<<< orphan*/  rx_used; } ;
struct iwl_rx_mem_buffer {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int RX_CLAIM_REQ_ALLOC ; 
 int RX_POST_REQ_ALLOC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_pcie_rx_move_to_allocator (struct iwl_rxq*,struct iwl_rb_allocator*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void iwl_pcie_rx_reuse_rbd(struct iwl_trans *trans,
				  struct iwl_rx_mem_buffer *rxb,
				  struct iwl_rxq *rxq, bool emergency)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_rb_allocator *rba = &trans_pcie->rba;

	/* Move the RBD to the used list, will be moved to allocator in batches
	 * before claiming or posting a request*/
	list_add_tail(&rxb->list, &rxq->rx_used);

	if (unlikely(emergency))
		return;

	/* Count the allocator owned RBDs */
	rxq->used_count++;

	/* If we have RX_POST_REQ_ALLOC new released rx buffers -
	 * issue a request for allocator. Modulo RX_CLAIM_REQ_ALLOC is
	 * used for the case we failed to claim RX_CLAIM_REQ_ALLOC,
	 * after but we still need to post another request.
	 */
	if ((rxq->used_count % RX_CLAIM_REQ_ALLOC) == RX_POST_REQ_ALLOC) {
		/* Move the 2 RBDs to the allocator ownership.
		 Allocator has another 6 from pool for the request completion*/
		iwl_pcie_rx_move_to_allocator(rxq, rba);

		atomic_inc(&rba->req_pending);
		queue_work(rba->alloc_wq, &rba->rx_alloc);
	}
}