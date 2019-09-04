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
typedef  scalar_t__ u8 ;
struct ice_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_NIC_FLX_ENTRY (struct ice_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ICE_NIC_FLX_FLG_ENTRY (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ICE_RXFLG_EVLAN_x8100 ; 
 int /*<<< orphan*/  ICE_RXFLG_EVLAN_x9100 ; 
 int /*<<< orphan*/  ICE_RXFLG_FIN ; 
 int /*<<< orphan*/  ICE_RXFLG_PKT_DSI ; 
 int /*<<< orphan*/  ICE_RXFLG_PKT_FRG ; 
 int /*<<< orphan*/  ICE_RXFLG_RST ; 
 int /*<<< orphan*/  ICE_RXFLG_SYN ; 
 int /*<<< orphan*/  ICE_RXFLG_TNL0 ; 
 int /*<<< orphan*/  ICE_RXFLG_TNL1 ; 
 int /*<<< orphan*/  ICE_RXFLG_TNL2 ; 
 int /*<<< orphan*/  ICE_RXFLG_TNL_MAC ; 
 int /*<<< orphan*/  ICE_RXFLG_TNL_VLAN ; 
 int /*<<< orphan*/  ICE_RXFLG_UDP_GRE ; 
 int /*<<< orphan*/  ICE_RXFLG_VLAN_x8100 ; 
 int /*<<< orphan*/  ICE_RX_MDID_FLOW_ID_HIGH ; 
 int /*<<< orphan*/  ICE_RX_MDID_FLOW_ID_LOWER ; 
 int /*<<< orphan*/  ICE_RX_MDID_HASH_HIGH ; 
 int /*<<< orphan*/  ICE_RX_MDID_HASH_LOW ; 

__attribute__((used)) static void ice_init_flex_parser(struct ice_hw *hw)
{
	u8 idx = 0;

	ICE_NIC_FLX_ENTRY(hw, ICE_RX_MDID_HASH_LOW, 0);
	ICE_NIC_FLX_ENTRY(hw, ICE_RX_MDID_HASH_HIGH, 1);
	ICE_NIC_FLX_ENTRY(hw, ICE_RX_MDID_FLOW_ID_LOWER, 2);
	ICE_NIC_FLX_ENTRY(hw, ICE_RX_MDID_FLOW_ID_HIGH, 3);
	ICE_NIC_FLX_FLG_ENTRY(hw, ICE_RXFLG_PKT_FRG, ICE_RXFLG_UDP_GRE,
			      ICE_RXFLG_PKT_DSI, ICE_RXFLG_FIN, idx++);
	ICE_NIC_FLX_FLG_ENTRY(hw, ICE_RXFLG_SYN, ICE_RXFLG_RST,
			      ICE_RXFLG_PKT_DSI, ICE_RXFLG_PKT_DSI, idx++);
	ICE_NIC_FLX_FLG_ENTRY(hw, ICE_RXFLG_PKT_DSI, ICE_RXFLG_PKT_DSI,
			      ICE_RXFLG_EVLAN_x8100, ICE_RXFLG_EVLAN_x9100,
			      idx++);
	ICE_NIC_FLX_FLG_ENTRY(hw, ICE_RXFLG_VLAN_x8100, ICE_RXFLG_TNL_VLAN,
			      ICE_RXFLG_TNL_MAC, ICE_RXFLG_TNL0, idx++);
	ICE_NIC_FLX_FLG_ENTRY(hw, ICE_RXFLG_TNL1, ICE_RXFLG_TNL2,
			      ICE_RXFLG_PKT_DSI, ICE_RXFLG_PKT_DSI, idx);
}