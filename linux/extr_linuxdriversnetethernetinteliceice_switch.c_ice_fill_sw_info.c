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
 scalar_t__ ICE_SW_LKUP_MAC ; 
 scalar_t__ is_unicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_fill_sw_info(struct ice_hw *hw, struct ice_fltr_info *f_info)
{
	f_info->lb_en = false;
	f_info->lan_en = false;
	if ((f_info->flag & ICE_FLTR_TX) &&
	    (f_info->fltr_act == ICE_FWD_TO_VSI ||
	     f_info->fltr_act == ICE_FWD_TO_VSI_LIST ||
	     f_info->fltr_act == ICE_FWD_TO_Q ||
	     f_info->fltr_act == ICE_FWD_TO_QGRP)) {
		f_info->lb_en = true;
		if (!(hw->evb_veb && f_info->lkup_type == ICE_SW_LKUP_MAC &&
		      is_unicast_ether_addr(f_info->l_data.mac.mac_addr)))
			f_info->lan_en = true;
	}
}