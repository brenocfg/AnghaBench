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
 int E1000_ADVTXD_DCMD_DEXT ; 
 int E1000_ADVTXD_DCMD_IFCS ; 
 int E1000_ADVTXD_DCMD_TSE ; 
 int E1000_ADVTXD_DCMD_VLE ; 
 int E1000_ADVTXD_DTYP_DATA ; 
 int E1000_ADVTXD_MAC_TSTAMP ; 
 int IGB_SET_FLAG (int,int,int) ; 
 int IGB_TX_FLAGS_TSO ; 
 int IGB_TX_FLAGS_TSTAMP ; 
 int IGB_TX_FLAGS_VLAN ; 

__attribute__((used)) static u32 igb_tx_cmd_type(struct sk_buff *skb, u32 tx_flags)
{
	/* set type for advanced descriptor with frame checksum insertion */
	u32 cmd_type = E1000_ADVTXD_DTYP_DATA |
		       E1000_ADVTXD_DCMD_DEXT |
		       E1000_ADVTXD_DCMD_IFCS;

	/* set HW vlan bit if vlan is present */
	cmd_type |= IGB_SET_FLAG(tx_flags, IGB_TX_FLAGS_VLAN,
				 (E1000_ADVTXD_DCMD_VLE));

	/* set segmentation bits for TSO */
	cmd_type |= IGB_SET_FLAG(tx_flags, IGB_TX_FLAGS_TSO,
				 (E1000_ADVTXD_DCMD_TSE));

	/* set timestamp bit if present */
	cmd_type |= IGB_SET_FLAG(tx_flags, IGB_TX_FLAGS_TSTAMP,
				 (E1000_ADVTXD_MAC_TSTAMP));

	/* insert frame checksum */
	cmd_type ^= IGB_SET_FLAG(skb->no_fcs, 1, E1000_ADVTXD_DCMD_IFCS);

	return cmd_type;
}