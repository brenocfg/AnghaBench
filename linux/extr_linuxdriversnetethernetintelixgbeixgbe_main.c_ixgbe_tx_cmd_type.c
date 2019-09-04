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
struct sk_buff {int no_fcs; } ;

/* Variables and functions */
 int IXGBE_ADVTXD_DCMD_DEXT ; 
 int IXGBE_ADVTXD_DCMD_IFCS ; 
 int IXGBE_ADVTXD_DCMD_TSE ; 
 int IXGBE_ADVTXD_DCMD_VLE ; 
 int IXGBE_ADVTXD_DTYP_DATA ; 
 int IXGBE_ADVTXD_MAC_TSTAMP ; 
 int IXGBE_SET_FLAG (int,int,int) ; 
 int IXGBE_TX_FLAGS_HW_VLAN ; 
 int IXGBE_TX_FLAGS_TSO ; 
 int IXGBE_TX_FLAGS_TSTAMP ; 

__attribute__((used)) static u32 ixgbe_tx_cmd_type(struct sk_buff *skb, u32 tx_flags)
{
	/* set type for advanced descriptor with frame checksum insertion */
	u32 cmd_type = IXGBE_ADVTXD_DTYP_DATA |
		       IXGBE_ADVTXD_DCMD_DEXT |
		       IXGBE_ADVTXD_DCMD_IFCS;

	/* set HW vlan bit if vlan is present */
	cmd_type |= IXGBE_SET_FLAG(tx_flags, IXGBE_TX_FLAGS_HW_VLAN,
				   IXGBE_ADVTXD_DCMD_VLE);

	/* set segmentation enable bits for TSO/FSO */
	cmd_type |= IXGBE_SET_FLAG(tx_flags, IXGBE_TX_FLAGS_TSO,
				   IXGBE_ADVTXD_DCMD_TSE);

	/* set timestamp bit if present */
	cmd_type |= IXGBE_SET_FLAG(tx_flags, IXGBE_TX_FLAGS_TSTAMP,
				   IXGBE_ADVTXD_MAC_TSTAMP);

	/* insert frame checksum */
	cmd_type ^= IXGBE_SET_FLAG(skb->no_fcs, 1, IXGBE_ADVTXD_DCMD_IFCS);

	return cmd_type;
}