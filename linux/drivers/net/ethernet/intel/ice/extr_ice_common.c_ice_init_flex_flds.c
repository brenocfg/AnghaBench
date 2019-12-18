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
struct ice_hw {int dummy; } ;
typedef  enum ice_rxdid { ____Placeholder_ice_rxdid } ice_rxdid ;
typedef  enum ice_flex_rx_mdid { ____Placeholder_ice_flex_rx_mdid } ice_flex_rx_mdid ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DBG_INIT ; 
 int /*<<< orphan*/  ICE_PROG_FLEX_ENTRY (struct ice_hw*,int,int,int) ; 
#define  ICE_RXDID_FLEX_NIC 129 
#define  ICE_RXDID_FLEX_NIC_2 128 
 int ICE_RX_MDID_FLOW_ID_HIGH ; 
 int ICE_RX_MDID_FLOW_ID_LOWER ; 
 int ICE_RX_MDID_HASH_HIGH ; 
 int ICE_RX_MDID_HASH_LOW ; 
 int ICE_RX_MDID_SRC_VSI ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ice_init_flex_flags (struct ice_hw*,int) ; 

__attribute__((used)) static void ice_init_flex_flds(struct ice_hw *hw, enum ice_rxdid prof_id)
{
	enum ice_flex_rx_mdid mdid;

	switch (prof_id) {
	case ICE_RXDID_FLEX_NIC:
	case ICE_RXDID_FLEX_NIC_2:
		ICE_PROG_FLEX_ENTRY(hw, prof_id, ICE_RX_MDID_HASH_LOW, 0);
		ICE_PROG_FLEX_ENTRY(hw, prof_id, ICE_RX_MDID_HASH_HIGH, 1);
		ICE_PROG_FLEX_ENTRY(hw, prof_id, ICE_RX_MDID_FLOW_ID_LOWER, 2);

		mdid = (prof_id == ICE_RXDID_FLEX_NIC_2) ?
			ICE_RX_MDID_SRC_VSI : ICE_RX_MDID_FLOW_ID_HIGH;

		ICE_PROG_FLEX_ENTRY(hw, prof_id, mdid, 3);

		ice_init_flex_flags(hw, prof_id);
		break;

	default:
		ice_debug(hw, ICE_DBG_INIT,
			  "Field init for profile ID %d not supported\n",
			  prof_id);
	}
}