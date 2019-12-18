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
typedef  scalar_t__ u16 ;
struct timespec64 {int tv_nsec; } ;
struct igc_tx_buffer {TYPE_1__* skb; } ;
struct igc_ring {scalar_t__ next_to_use; scalar_t__ count; int reg_idx; scalar_t__ launchtime_enable; int /*<<< orphan*/  flags; } ;
struct igc_adv_tx_context_desc {void* launch_time; void* mss_l4len_idx; void* type_tucmd_mlhl; void* vlan_macip_lens; } ;
struct TYPE_2__ {int /*<<< orphan*/  tstamp; } ;

/* Variables and functions */
 int IGC_ADVTXD_DTYP_CTXT ; 
 int /*<<< orphan*/  IGC_RING_FLAG_TX_CTX_IDX ; 
 int IGC_TXD_CMD_DEXT ; 
 struct igc_adv_tx_context_desc* IGC_TX_CTXTDESC (struct igc_ring*,scalar_t__) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igc_tx_ctxtdesc(struct igc_ring *tx_ring,
			    struct igc_tx_buffer *first,
			    u32 vlan_macip_lens, u32 type_tucmd,
			    u32 mss_l4len_idx)
{
	struct igc_adv_tx_context_desc *context_desc;
	u16 i = tx_ring->next_to_use;
	struct timespec64 ts;

	context_desc = IGC_TX_CTXTDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	/* set bits to identify this as an advanced context descriptor */
	type_tucmd |= IGC_TXD_CMD_DEXT | IGC_ADVTXD_DTYP_CTXT;

	/* For 82575, context index must be unique per ring. */
	if (test_bit(IGC_RING_FLAG_TX_CTX_IDX, &tx_ring->flags))
		mss_l4len_idx |= tx_ring->reg_idx << 4;

	context_desc->vlan_macip_lens	= cpu_to_le32(vlan_macip_lens);
	context_desc->type_tucmd_mlhl	= cpu_to_le32(type_tucmd);
	context_desc->mss_l4len_idx	= cpu_to_le32(mss_l4len_idx);

	/* We assume there is always a valid Tx time available. Invalid times
	 * should have been handled by the upper layers.
	 */
	if (tx_ring->launchtime_enable) {
		ts = ktime_to_timespec64(first->skb->tstamp);
		first->skb->tstamp = ktime_set(0, 0);
		context_desc->launch_time = cpu_to_le32(ts.tv_nsec / 32);
	} else {
		context_desc->launch_time = 0;
	}
}