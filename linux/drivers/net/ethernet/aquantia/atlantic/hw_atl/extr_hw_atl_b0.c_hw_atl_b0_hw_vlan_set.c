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
struct aq_rx_filter_vlan {int queue; int /*<<< orphan*/  vlan_id; scalar_t__ enable; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int AQ_VLAN_MAX_FILTERS ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_flr_act_set (struct aq_hw_s*,unsigned int,int) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_flr_en_set (struct aq_hw_s*,unsigned int,int) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_id_flr_set (struct aq_hw_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_rxq_en_flr_set (struct aq_hw_s*,unsigned int,int) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_rxq_flr_set (struct aq_hw_s*,int,int) ; 

__attribute__((used)) static int hw_atl_b0_hw_vlan_set(struct aq_hw_s *self,
				 struct aq_rx_filter_vlan *aq_vlans)
{
	int i;

	for (i = 0; i < AQ_VLAN_MAX_FILTERS; i++) {
		hw_atl_rpf_vlan_flr_en_set(self, 0U, i);
		hw_atl_rpf_vlan_rxq_en_flr_set(self, 0U, i);
		if (aq_vlans[i].enable) {
			hw_atl_rpf_vlan_id_flr_set(self,
						   aq_vlans[i].vlan_id,
						   i);
			hw_atl_rpf_vlan_flr_act_set(self, 1U, i);
			hw_atl_rpf_vlan_flr_en_set(self, 1U, i);
			if (aq_vlans[i].queue != 0xFF) {
				hw_atl_rpf_vlan_rxq_flr_set(self,
							    aq_vlans[i].queue,
							    i);
				hw_atl_rpf_vlan_rxq_en_flr_set(self, 1U, i);
			}
		}
	}

	return aq_hw_err_from_flags(self);
}