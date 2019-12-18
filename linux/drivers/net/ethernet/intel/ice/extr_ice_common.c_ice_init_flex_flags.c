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
typedef  int /*<<< orphan*/  u8 ;
struct ice_hw {int dummy; } ;
typedef  enum ice_rxdid { ____Placeholder_ice_rxdid } ice_rxdid ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DBG_INIT ; 
 int /*<<< orphan*/  ICE_FLG_EVLAN_x8100 ; 
 int /*<<< orphan*/  ICE_FLG_EVLAN_x9100 ; 
 int /*<<< orphan*/  ICE_FLG_FIN ; 
 int /*<<< orphan*/  ICE_FLG_PKT_DSI ; 
 int /*<<< orphan*/  ICE_FLG_PKT_FRG ; 
 int /*<<< orphan*/  ICE_FLG_RST ; 
 int /*<<< orphan*/  ICE_FLG_SYN ; 
 int /*<<< orphan*/  ICE_FLG_TNL0 ; 
 int /*<<< orphan*/  ICE_FLG_TNL1 ; 
 int /*<<< orphan*/  ICE_FLG_TNL2 ; 
 int /*<<< orphan*/  ICE_FLG_TNL_MAC ; 
 int /*<<< orphan*/  ICE_FLG_TNL_VLAN ; 
 int /*<<< orphan*/  ICE_FLG_UDP_GRE ; 
 int /*<<< orphan*/  ICE_FLG_VLAN_x8100 ; 
 int /*<<< orphan*/  ICE_PROG_FLG_ENTRY (struct ice_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ICE_RXDID_FLEX_NIC 129 
#define  ICE_RXDID_FLEX_NIC_2 128 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ice_init_flex_flags(struct ice_hw *hw, enum ice_rxdid prof_id)
{
	u8 idx = 0;

	/* Flex-flag fields (0-2) are programmed with FLG64 bits with layout:
	 * flexiflags0[5:0] - TCP flags, is_packet_fragmented, is_packet_UDP_GRE
	 * flexiflags1[3:0] - Not used for flag programming
	 * flexiflags2[7:0] - Tunnel and VLAN types
	 * 2 invalid fields in last index
	 */
	switch (prof_id) {
	/* Rx flex flags are currently programmed for the NIC profiles only.
	 * Different flag bit programming configurations can be added per
	 * profile as needed.
	 */
	case ICE_RXDID_FLEX_NIC:
	case ICE_RXDID_FLEX_NIC_2:
		ICE_PROG_FLG_ENTRY(hw, prof_id, ICE_FLG_PKT_FRG,
				   ICE_FLG_UDP_GRE, ICE_FLG_PKT_DSI,
				   ICE_FLG_FIN, idx++);
		/* flex flag 1 is not used for flexi-flag programming, skipping
		 * these four FLG64 bits.
		 */
		ICE_PROG_FLG_ENTRY(hw, prof_id, ICE_FLG_SYN, ICE_FLG_RST,
				   ICE_FLG_PKT_DSI, ICE_FLG_PKT_DSI, idx++);
		ICE_PROG_FLG_ENTRY(hw, prof_id, ICE_FLG_PKT_DSI,
				   ICE_FLG_PKT_DSI, ICE_FLG_EVLAN_x8100,
				   ICE_FLG_EVLAN_x9100, idx++);
		ICE_PROG_FLG_ENTRY(hw, prof_id, ICE_FLG_VLAN_x8100,
				   ICE_FLG_TNL_VLAN, ICE_FLG_TNL_MAC,
				   ICE_FLG_TNL0, idx++);
		ICE_PROG_FLG_ENTRY(hw, prof_id, ICE_FLG_TNL1, ICE_FLG_TNL2,
				   ICE_FLG_PKT_DSI, ICE_FLG_PKT_DSI, idx);
		break;

	default:
		ice_debug(hw, ICE_DBG_INIT,
			  "Flag programming for profile ID %d not supported\n",
			  prof_id);
	}
}