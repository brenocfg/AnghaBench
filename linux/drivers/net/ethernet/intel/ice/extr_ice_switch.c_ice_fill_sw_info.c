#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ice_hw {scalar_t__ evb_veb; } ;
struct TYPE_3__ {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct ice_fltr_info {int lb_en; int lan_en; int flag; scalar_t__ fltr_act; scalar_t__ lkup_type; TYPE_2__ l_data; } ;

/* Variables and functions */
 int ICE_FLTR_TX ; 
 scalar_t__ ICE_FWD_TO_Q ; 
 scalar_t__ ICE_FWD_TO_QGRP ; 
 scalar_t__ ICE_FWD_TO_VSI ; 
 scalar_t__ ICE_FWD_TO_VSI_LIST ; 
 scalar_t__ ICE_SW_LKUP_DFLT ; 
 scalar_t__ ICE_SW_LKUP_ETHERTYPE ; 
 scalar_t__ ICE_SW_LKUP_ETHERTYPE_MAC ; 
 scalar_t__ ICE_SW_LKUP_MAC ; 
 scalar_t__ ICE_SW_LKUP_MAC_VLAN ; 
 scalar_t__ ICE_SW_LKUP_PROMISC ; 
 scalar_t__ ICE_SW_LKUP_PROMISC_VLAN ; 
 scalar_t__ ICE_SW_LKUP_VLAN ; 
 int /*<<< orphan*/  is_unicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_fill_sw_info(struct ice_hw *hw, struct ice_fltr_info *fi)
{
	fi->lb_en = false;
	fi->lan_en = false;
	if ((fi->flag & ICE_FLTR_TX) &&
	    (fi->fltr_act == ICE_FWD_TO_VSI ||
	     fi->fltr_act == ICE_FWD_TO_VSI_LIST ||
	     fi->fltr_act == ICE_FWD_TO_Q ||
	     fi->fltr_act == ICE_FWD_TO_QGRP)) {
		/* Setting LB for prune actions will result in replicated
		 * packets to the internal switch that will be dropped.
		 */
		if (fi->lkup_type != ICE_SW_LKUP_VLAN)
			fi->lb_en = true;

		/* Set lan_en to TRUE if
		 * 1. The switch is a VEB AND
		 * 2
		 * 2.1 The lookup is a directional lookup like ethertype,
		 * promiscuous, ethertype-MAC, promiscuous-VLAN
		 * and default-port OR
		 * 2.2 The lookup is VLAN, OR
		 * 2.3 The lookup is MAC with mcast or bcast addr for MAC, OR
		 * 2.4 The lookup is MAC_VLAN with mcast or bcast addr for MAC.
		 *
		 * OR
		 *
		 * The switch is a VEPA.
		 *
		 * In all other cases, the LAN enable has to be set to false.
		 */
		if (hw->evb_veb) {
			if (fi->lkup_type == ICE_SW_LKUP_ETHERTYPE ||
			    fi->lkup_type == ICE_SW_LKUP_PROMISC ||
			    fi->lkup_type == ICE_SW_LKUP_ETHERTYPE_MAC ||
			    fi->lkup_type == ICE_SW_LKUP_PROMISC_VLAN ||
			    fi->lkup_type == ICE_SW_LKUP_DFLT ||
			    fi->lkup_type == ICE_SW_LKUP_VLAN ||
			    (fi->lkup_type == ICE_SW_LKUP_MAC &&
			     !is_unicast_ether_addr(fi->l_data.mac.mac_addr)) ||
			    (fi->lkup_type == ICE_SW_LKUP_MAC_VLAN &&
			     !is_unicast_ether_addr(fi->l_data.mac.mac_addr)))
				fi->lan_en = true;
		} else {
			fi->lan_en = true;
		}
	}
}