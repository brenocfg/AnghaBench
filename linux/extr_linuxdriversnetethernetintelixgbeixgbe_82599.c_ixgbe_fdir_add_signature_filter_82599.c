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
struct TYPE_2__ {int flow_type; } ;
union ixgbe_atr_hash_dword {TYPE_1__ formatted; } ;
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  IXGBE_ATR_FLOW_TYPE_SCTPV4 133 
#define  IXGBE_ATR_FLOW_TYPE_SCTPV6 132 
#define  IXGBE_ATR_FLOW_TYPE_TCPV4 131 
#define  IXGBE_ATR_FLOW_TYPE_TCPV6 130 
#define  IXGBE_ATR_FLOW_TYPE_UDPV4 129 
#define  IXGBE_ATR_FLOW_TYPE_UDPV6 128 
 int IXGBE_ATR_L4TYPE_TUNNEL_MASK ; 
 int /*<<< orphan*/  IXGBE_ERR_CONFIG ; 
 int IXGBE_FDIRCMD_CMD_ADD_FLOW ; 
 int IXGBE_FDIRCMD_FILTER_UPDATE ; 
 int IXGBE_FDIRCMD_FLOW_TYPE_SHIFT ; 
 int IXGBE_FDIRCMD_LAST ; 
 int IXGBE_FDIRCMD_QUEUE_EN ; 
 int IXGBE_FDIRCMD_RX_QUEUE_SHIFT ; 
 int IXGBE_FDIRCMD_TUNNEL_FILTER ; 
 int /*<<< orphan*/  IXGBE_FDIRHASH ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG64 (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,...) ; 
 int ixgbe_atr_compute_sig_hash_82599 (union ixgbe_atr_hash_dword,union ixgbe_atr_hash_dword) ; 

s32 ixgbe_fdir_add_signature_filter_82599(struct ixgbe_hw *hw,
					  union ixgbe_atr_hash_dword input,
					  union ixgbe_atr_hash_dword common,
					  u8 queue)
{
	u64 fdirhashcmd;
	u8 flow_type;
	bool tunnel;
	u32 fdircmd;

	/*
	 * Get the flow_type in order to program FDIRCMD properly
	 * lowest 2 bits are FDIRCMD.L4TYPE, third lowest bit is FDIRCMD.IPV6
	 */
	tunnel = !!(input.formatted.flow_type & IXGBE_ATR_L4TYPE_TUNNEL_MASK);
	flow_type = input.formatted.flow_type &
		    (IXGBE_ATR_L4TYPE_TUNNEL_MASK - 1);
	switch (flow_type) {
	case IXGBE_ATR_FLOW_TYPE_TCPV4:
	case IXGBE_ATR_FLOW_TYPE_UDPV4:
	case IXGBE_ATR_FLOW_TYPE_SCTPV4:
	case IXGBE_ATR_FLOW_TYPE_TCPV6:
	case IXGBE_ATR_FLOW_TYPE_UDPV6:
	case IXGBE_ATR_FLOW_TYPE_SCTPV6:
		break;
	default:
		hw_dbg(hw, " Error on flow type input\n");
		return IXGBE_ERR_CONFIG;
	}

	/* configure FDIRCMD register */
	fdircmd = IXGBE_FDIRCMD_CMD_ADD_FLOW | IXGBE_FDIRCMD_FILTER_UPDATE |
		  IXGBE_FDIRCMD_LAST | IXGBE_FDIRCMD_QUEUE_EN;
	fdircmd |= (u32)flow_type << IXGBE_FDIRCMD_FLOW_TYPE_SHIFT;
	fdircmd |= (u32)queue << IXGBE_FDIRCMD_RX_QUEUE_SHIFT;
	if (tunnel)
		fdircmd |= IXGBE_FDIRCMD_TUNNEL_FILTER;

	/*
	 * The lower 32-bits of fdirhashcmd is for FDIRHASH, the upper 32-bits
	 * is for FDIRCMD.  Then do a 64-bit register write from FDIRHASH.
	 */
	fdirhashcmd = (u64)fdircmd << 32;
	fdirhashcmd |= ixgbe_atr_compute_sig_hash_82599(input, common);
	IXGBE_WRITE_REG64(hw, IXGBE_FDIRHASH, fdirhashcmd);

	hw_dbg(hw, "Tx Queue=%x hash=%x\n", queue, (u32)fdirhashcmd);

	return 0;
}