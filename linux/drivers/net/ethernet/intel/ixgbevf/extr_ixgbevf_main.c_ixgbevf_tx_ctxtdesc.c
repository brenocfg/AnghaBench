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
typedef  scalar_t__ u16 ;
struct ixgbevf_ring {scalar_t__ next_to_use; scalar_t__ count; } ;
struct ixgbe_adv_tx_context_desc {void* mss_l4len_idx; void* type_tucmd_mlhl; void* fceof_saidx; void* vlan_macip_lens; } ;

/* Variables and functions */
 struct ixgbe_adv_tx_context_desc* IXGBEVF_TX_CTXTDESC (struct ixgbevf_ring*,scalar_t__) ; 
 int IXGBE_ADVTXD_DTYP_CTXT ; 
 int IXGBE_TXD_CMD_DEXT ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void ixgbevf_tx_ctxtdesc(struct ixgbevf_ring *tx_ring,
				u32 vlan_macip_lens, u32 fceof_saidx,
				u32 type_tucmd, u32 mss_l4len_idx)
{
	struct ixgbe_adv_tx_context_desc *context_desc;
	u16 i = tx_ring->next_to_use;

	context_desc = IXGBEVF_TX_CTXTDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	/* set bits to identify this as an advanced context descriptor */
	type_tucmd |= IXGBE_TXD_CMD_DEXT | IXGBE_ADVTXD_DTYP_CTXT;

	context_desc->vlan_macip_lens	= cpu_to_le32(vlan_macip_lens);
	context_desc->fceof_saidx	= cpu_to_le32(fceof_saidx);
	context_desc->type_tucmd_mlhl	= cpu_to_le32(type_tucmd);
	context_desc->mss_l4len_idx	= cpu_to_le32(mss_l4len_idx);
}