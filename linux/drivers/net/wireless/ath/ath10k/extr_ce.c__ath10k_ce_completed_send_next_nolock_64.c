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
struct ce_desc_64 {scalar_t__ nbytes; } ;
struct ath10k_ce_ring {unsigned int nentries_mask; unsigned int sw_index; unsigned int hw_index; int /*<<< orphan*/  base_addr_owner_space; int /*<<< orphan*/ ** per_transfer_context; } ;
struct ath10k_ce_pipe {struct ath10k* ar; int /*<<< orphan*/  ctrl_addr; struct ath10k_ce_ring* src_ring; } ;
struct TYPE_2__ {scalar_t__ rri_on_ddr; } ;
struct ath10k {TYPE_1__ hw_params; } ;

/* Variables and functions */
 unsigned int CE_RING_IDX_INCR (unsigned int,unsigned int) ; 
 struct ce_desc_64* CE_SRC_RING_TO_DESC_64 (int /*<<< orphan*/ ,unsigned int) ; 
 int EIO ; 
 int ENODEV ; 
 unsigned int ath10k_ce_src_ring_read_index_get (struct ath10k*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ath10k_ce_completed_send_next_nolock_64(struct ath10k_ce_pipe *ce_state,
						    void **per_transfer_contextp)
{
	struct ath10k_ce_ring *src_ring = ce_state->src_ring;
	u32 ctrl_addr = ce_state->ctrl_addr;
	struct ath10k *ar = ce_state->ar;
	unsigned int nentries_mask = src_ring->nentries_mask;
	unsigned int sw_index = src_ring->sw_index;
	unsigned int read_index;
	struct ce_desc_64 *desc;

	if (src_ring->hw_index == sw_index) {
		/*
		 * The SW completion index has caught up with the cached
		 * version of the HW completion index.
		 * Update the cached HW completion index to see whether
		 * the SW has really caught up to the HW, or if the cached
		 * value of the HW index has become stale.
		 */

		read_index = ath10k_ce_src_ring_read_index_get(ar, ctrl_addr);
		if (read_index == 0xffffffff)
			return -ENODEV;

		read_index &= nentries_mask;
		src_ring->hw_index = read_index;
	}

	if (ar->hw_params.rri_on_ddr)
		read_index = ath10k_ce_src_ring_read_index_get(ar, ctrl_addr);
	else
		read_index = src_ring->hw_index;

	if (read_index == sw_index)
		return -EIO;

	if (per_transfer_contextp)
		*per_transfer_contextp =
			src_ring->per_transfer_context[sw_index];

	/* sanity */
	src_ring->per_transfer_context[sw_index] = NULL;
	desc = CE_SRC_RING_TO_DESC_64(src_ring->base_addr_owner_space,
				      sw_index);
	desc->nbytes = 0;

	/* Update sw_index */
	sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
	src_ring->sw_index = sw_index;

	return 0;
}