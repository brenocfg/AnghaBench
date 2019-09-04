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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int IXGBE_ADVTXD_DCMD_DEXT ; 
 int IXGBE_ADVTXD_DCMD_IFCS ; 
 int IXGBE_ADVTXD_DCMD_TSE ; 
 int IXGBE_ADVTXD_DCMD_VLE ; 
 int IXGBE_ADVTXD_DTYP_DATA ; 
 int IXGBE_TX_FLAGS_TSO ; 
 int IXGBE_TX_FLAGS_VLAN ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static __le32 ixgbevf_tx_cmd_type(u32 tx_flags)
{
	/* set type for advanced descriptor with frame checksum insertion */
	__le32 cmd_type = cpu_to_le32(IXGBE_ADVTXD_DTYP_DATA |
				      IXGBE_ADVTXD_DCMD_IFCS |
				      IXGBE_ADVTXD_DCMD_DEXT);

	/* set HW VLAN bit if VLAN is present */
	if (tx_flags & IXGBE_TX_FLAGS_VLAN)
		cmd_type |= cpu_to_le32(IXGBE_ADVTXD_DCMD_VLE);

	/* set segmentation enable bits for TSO/FSO */
	if (tx_flags & IXGBE_TX_FLAGS_TSO)
		cmd_type |= cpu_to_le32(IXGBE_ADVTXD_DCMD_TSE);

	return cmd_type;
}