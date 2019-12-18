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
struct ce_desc_64 {scalar_t__ nbytes; int /*<<< orphan*/  addr; } ;
struct ath10k_ce_ring {unsigned int nentries_mask; unsigned int sw_index; unsigned int write_index; int /*<<< orphan*/ ** per_transfer_context; struct ce_desc_64* base_addr_owner_space; } ;
struct ath10k_ce_pipe {struct ath10k* ar; struct ath10k_ce_ring* dest_ring; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; } ;
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct ce_desc_64* CE_DEST_RING_TO_DESC_64 (struct ce_desc_64*,unsigned int) ; 
 unsigned int CE_RING_IDX_INCR (unsigned int,unsigned int) ; 
 int EIO ; 
 int /*<<< orphan*/  __le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _ath10k_ce_revoke_recv_next_64(struct ath10k_ce_pipe *ce_state,
					  void **per_transfer_contextp,
					  dma_addr_t *bufferp)
{
	struct ath10k_ce_ring *dest_ring;
	unsigned int nentries_mask;
	unsigned int sw_index;
	unsigned int write_index;
	int ret;
	struct ath10k *ar;
	struct ath10k_ce *ce;

	dest_ring = ce_state->dest_ring;

	if (!dest_ring)
		return -EIO;

	ar = ce_state->ar;
	ce = ath10k_ce_priv(ar);

	spin_lock_bh(&ce->ce_lock);

	nentries_mask = dest_ring->nentries_mask;
	sw_index = dest_ring->sw_index;
	write_index = dest_ring->write_index;
	if (write_index != sw_index) {
		struct ce_desc_64 *base = dest_ring->base_addr_owner_space;
		struct ce_desc_64 *desc =
			CE_DEST_RING_TO_DESC_64(base, sw_index);

		/* Return data from completed destination descriptor */
		*bufferp = __le64_to_cpu(desc->addr);

		if (per_transfer_contextp)
			*per_transfer_contextp =
				dest_ring->per_transfer_context[sw_index];

		/* sanity */
		dest_ring->per_transfer_context[sw_index] = NULL;
		desc->nbytes = 0;

		/* Update sw_index */
		sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
		dest_ring->sw_index = sw_index;
		ret = 0;
	} else {
		ret = -EIO;
	}

	spin_unlock_bh(&ce->ce_lock);

	return ret;
}