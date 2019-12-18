#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  void* u16 ;
struct ice_hw {TYPE_4__* port_info; } ;
struct TYPE_10__ {void* hw_vsi_id; } ;
struct TYPE_7__ {int* mac_addr; } ;
struct TYPE_6__ {void* vlan_id; } ;
struct TYPE_8__ {TYPE_2__ mac; TYPE_1__ mac_vlan; } ;
struct ice_fltr_info {TYPE_5__ fwd_id; void* vsi_handle; int /*<<< orphan*/  fltr_act; void* src; int /*<<< orphan*/  flag; TYPE_3__ l_data; void* lkup_type; } ;
struct ice_fltr_list_entry {struct ice_fltr_info fltr_info; } ;
typedef  int /*<<< orphan*/  new_fltr ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_9__ {void* lport; } ;

/* Variables and functions */
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  ICE_FLTR_RX ; 
 int /*<<< orphan*/  ICE_FLTR_TX ; 
 int /*<<< orphan*/  ICE_FWD_TO_VSI ; 
 int ICE_PROMISC_BCAST_RX ; 
 int ICE_PROMISC_BCAST_TX ; 
 int ICE_PROMISC_MCAST_RX ; 
 int ICE_PROMISC_MCAST_TX ; 
 int ICE_PROMISC_UCAST_RX ; 
 int ICE_PROMISC_UCAST_TX ; 
 int ICE_PROMISC_VLAN_RX ; 
 int ICE_PROMISC_VLAN_TX ; 
 void* ICE_SW_LKUP_PROMISC ; 
 void* ICE_SW_LKUP_PROMISC_VLAN ; 
 int /*<<< orphan*/  dummy_eth_header ; 
 int /*<<< orphan*/  eth_broadcast_addr (int*) ; 
 int /*<<< orphan*/  ether_addr_copy (int*,int /*<<< orphan*/ ) ; 
 int ice_add_rule_internal (struct ice_hw*,int,struct ice_fltr_list_entry*) ; 
 void* ice_get_hw_vsi_num (struct ice_hw*,void*) ; 
 int /*<<< orphan*/  ice_is_vsi_valid (struct ice_hw*,void*) ; 
 int /*<<< orphan*/  memset (struct ice_fltr_info*,int /*<<< orphan*/ ,int) ; 

enum ice_status
ice_set_vsi_promisc(struct ice_hw *hw, u16 vsi_handle, u8 promisc_mask, u16 vid)
{
	enum { UCAST_FLTR = 1, MCAST_FLTR, BCAST_FLTR };
	struct ice_fltr_list_entry f_list_entry;
	struct ice_fltr_info new_fltr;
	enum ice_status status = 0;
	bool is_tx_fltr;
	u16 hw_vsi_id;
	int pkt_type;
	u8 recipe_id;

	if (!ice_is_vsi_valid(hw, vsi_handle))
		return ICE_ERR_PARAM;
	hw_vsi_id = ice_get_hw_vsi_num(hw, vsi_handle);

	memset(&new_fltr, 0, sizeof(new_fltr));

	if (promisc_mask & (ICE_PROMISC_VLAN_RX | ICE_PROMISC_VLAN_TX)) {
		new_fltr.lkup_type = ICE_SW_LKUP_PROMISC_VLAN;
		new_fltr.l_data.mac_vlan.vlan_id = vid;
		recipe_id = ICE_SW_LKUP_PROMISC_VLAN;
	} else {
		new_fltr.lkup_type = ICE_SW_LKUP_PROMISC;
		recipe_id = ICE_SW_LKUP_PROMISC;
	}

	/* Separate filters must be set for each direction/packet type
	 * combination, so we will loop over the mask value, store the
	 * individual type, and clear it out in the input mask as it
	 * is found.
	 */
	while (promisc_mask) {
		u8 *mac_addr;

		pkt_type = 0;
		is_tx_fltr = false;

		if (promisc_mask & ICE_PROMISC_UCAST_RX) {
			promisc_mask &= ~ICE_PROMISC_UCAST_RX;
			pkt_type = UCAST_FLTR;
		} else if (promisc_mask & ICE_PROMISC_UCAST_TX) {
			promisc_mask &= ~ICE_PROMISC_UCAST_TX;
			pkt_type = UCAST_FLTR;
			is_tx_fltr = true;
		} else if (promisc_mask & ICE_PROMISC_MCAST_RX) {
			promisc_mask &= ~ICE_PROMISC_MCAST_RX;
			pkt_type = MCAST_FLTR;
		} else if (promisc_mask & ICE_PROMISC_MCAST_TX) {
			promisc_mask &= ~ICE_PROMISC_MCAST_TX;
			pkt_type = MCAST_FLTR;
			is_tx_fltr = true;
		} else if (promisc_mask & ICE_PROMISC_BCAST_RX) {
			promisc_mask &= ~ICE_PROMISC_BCAST_RX;
			pkt_type = BCAST_FLTR;
		} else if (promisc_mask & ICE_PROMISC_BCAST_TX) {
			promisc_mask &= ~ICE_PROMISC_BCAST_TX;
			pkt_type = BCAST_FLTR;
			is_tx_fltr = true;
		}

		/* Check for VLAN promiscuous flag */
		if (promisc_mask & ICE_PROMISC_VLAN_RX) {
			promisc_mask &= ~ICE_PROMISC_VLAN_RX;
		} else if (promisc_mask & ICE_PROMISC_VLAN_TX) {
			promisc_mask &= ~ICE_PROMISC_VLAN_TX;
			is_tx_fltr = true;
		}

		/* Set filter DA based on packet type */
		mac_addr = new_fltr.l_data.mac.mac_addr;
		if (pkt_type == BCAST_FLTR) {
			eth_broadcast_addr(mac_addr);
		} else if (pkt_type == MCAST_FLTR ||
			   pkt_type == UCAST_FLTR) {
			/* Use the dummy ether header DA */
			ether_addr_copy(mac_addr, dummy_eth_header);
			if (pkt_type == MCAST_FLTR)
				mac_addr[0] |= 0x1;	/* Set multicast bit */
		}

		/* Need to reset this to zero for all iterations */
		new_fltr.flag = 0;
		if (is_tx_fltr) {
			new_fltr.flag |= ICE_FLTR_TX;
			new_fltr.src = hw_vsi_id;
		} else {
			new_fltr.flag |= ICE_FLTR_RX;
			new_fltr.src = hw->port_info->lport;
		}

		new_fltr.fltr_act = ICE_FWD_TO_VSI;
		new_fltr.vsi_handle = vsi_handle;
		new_fltr.fwd_id.hw_vsi_id = hw_vsi_id;
		f_list_entry.fltr_info = new_fltr;

		status = ice_add_rule_internal(hw, recipe_id, &f_list_entry);
		if (status)
			goto set_promisc_exit;
	}

set_promisc_exit:
	return status;
}