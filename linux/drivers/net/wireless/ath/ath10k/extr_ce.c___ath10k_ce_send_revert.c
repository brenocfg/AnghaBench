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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_ce_ring {size_t write_index; size_t sw_index; size_t nentries_mask; int /*<<< orphan*/ ** per_transfer_context; } ;
struct ath10k_ce_pipe {int /*<<< orphan*/  ctrl_addr; struct ath10k_ce_ring* src_ring; struct ath10k* ar; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 size_t ath10k_ce_src_ring_write_index_get (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void __ath10k_ce_send_revert(struct ath10k_ce_pipe *pipe)
{
	struct ath10k *ar = pipe->ar;
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	struct ath10k_ce_ring *src_ring = pipe->src_ring;
	u32 ctrl_addr = pipe->ctrl_addr;

	lockdep_assert_held(&ce->ce_lock);

	/*
	 * This function must be called only if there is an incomplete
	 * scatter-gather transfer (before index register is updated)
	 * that needs to be cleaned up.
	 */
	if (WARN_ON_ONCE(src_ring->write_index == src_ring->sw_index))
		return;

	if (WARN_ON_ONCE(src_ring->write_index ==
			 ath10k_ce_src_ring_write_index_get(ar, ctrl_addr)))
		return;

	src_ring->write_index--;
	src_ring->write_index &= src_ring->nentries_mask;

	src_ring->per_transfer_context[src_ring->write_index] = NULL;
}