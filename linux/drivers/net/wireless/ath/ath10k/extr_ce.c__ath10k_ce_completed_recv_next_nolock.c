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
typedef  unsigned int u16 ;
struct ce_desc {scalar_t__ nbytes; } ;
struct ath10k_ce_ring {unsigned int nentries_mask; unsigned int sw_index; int /*<<< orphan*/ ** per_transfer_context; struct ce_desc* base_addr_owner_space; } ;
struct ath10k_ce_pipe {int id; struct ath10k_ce_ring* dest_ring; } ;

/* Variables and functions */
 struct ce_desc* CE_DEST_RING_TO_DESC (struct ce_desc*,unsigned int) ; 
 unsigned int CE_RING_IDX_INCR (unsigned int,unsigned int) ; 
 int EIO ; 
 unsigned int __le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static int
	 _ath10k_ce_completed_recv_next_nolock(struct ath10k_ce_pipe *ce_state,
					       void **per_transfer_contextp,
					       unsigned int *nbytesp)
{
	struct ath10k_ce_ring *dest_ring = ce_state->dest_ring;
	unsigned int nentries_mask = dest_ring->nentries_mask;
	unsigned int sw_index = dest_ring->sw_index;

	struct ce_desc *base = dest_ring->base_addr_owner_space;
	struct ce_desc *desc = CE_DEST_RING_TO_DESC(base, sw_index);
	struct ce_desc sdesc;
	u16 nbytes;

	/* Copy in one go for performance reasons */
	sdesc = *desc;

	nbytes = __le16_to_cpu(sdesc.nbytes);
	if (nbytes == 0) {
		/*
		 * This closes a relatively unusual race where the Host
		 * sees the updated DRRI before the update to the
		 * corresponding descriptor has completed. We treat this
		 * as a descriptor that is not yet done.
		 */
		return -EIO;
	}

	desc->nbytes = 0;

	/* Return data from completed destination descriptor */
	*nbytesp = nbytes;

	if (per_transfer_contextp)
		*per_transfer_contextp =
			dest_ring->per_transfer_context[sw_index];

	/* Copy engine 5 (HTT Rx) will reuse the same transfer context.
	 * So update transfer context all CEs except CE5.
	 */
	if (ce_state->id != 5)
		dest_ring->per_transfer_context[sw_index] = NULL;

	/* Update sw_index */
	sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
	dest_ring->sw_index = sw_index;

	return 0;
}