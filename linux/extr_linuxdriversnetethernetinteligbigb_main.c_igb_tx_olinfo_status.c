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
struct TYPE_2__ {int /*<<< orphan*/  olinfo_status; } ;
union e1000_adv_tx_desc {TYPE_1__ read; } ;
typedef  int u32 ;
struct igb_ring {int reg_idx; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int E1000_ADVTXD_PAYLEN_SHIFT ; 
 int E1000_TXD_POPTS_IXSM ; 
 int E1000_TXD_POPTS_TXSM ; 
 int /*<<< orphan*/  IGB_RING_FLAG_TX_CTX_IDX ; 
 int IGB_SET_FLAG (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IGB_TX_FLAGS_CSUM ; 
 int /*<<< orphan*/  IGB_TX_FLAGS_IPV4 ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igb_tx_olinfo_status(struct igb_ring *tx_ring,
				 union e1000_adv_tx_desc *tx_desc,
				 u32 tx_flags, unsigned int paylen)
{
	u32 olinfo_status = paylen << E1000_ADVTXD_PAYLEN_SHIFT;

	/* 82575 requires a unique index per ring */
	if (test_bit(IGB_RING_FLAG_TX_CTX_IDX, &tx_ring->flags))
		olinfo_status |= tx_ring->reg_idx << 4;

	/* insert L4 checksum */
	olinfo_status |= IGB_SET_FLAG(tx_flags,
				      IGB_TX_FLAGS_CSUM,
				      (E1000_TXD_POPTS_TXSM << 8));

	/* insert IPv4 checksum */
	olinfo_status |= IGB_SET_FLAG(tx_flags,
				      IGB_TX_FLAGS_IPV4,
				      (E1000_TXD_POPTS_IXSM << 8));

	tx_desc->read.olinfo_status = cpu_to_le32(olinfo_status);
}