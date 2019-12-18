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
struct aq_hw_s {TYPE_1__* aq_nic_cfg; } ;
struct TYPE_2__ {unsigned int mc_list_count; scalar_t__ is_mc_list_enabled; } ;

/* Variables and functions */
 unsigned int HW_ATL_A0_MAC_MAX ; 
 unsigned int HW_ATL_A0_MAC_MIN ; 
 int /*<<< orphan*/  IFF_BROADCAST ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
 int /*<<< orphan*/  IFF_PROMISC ; 
 scalar_t__ IS_FILTER_ENABLED (int /*<<< orphan*/ ) ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rpfl2_uc_flr_en_set (struct aq_hw_s*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpfl2broadcast_en_set (struct aq_hw_s*,scalar_t__) ; 
 int /*<<< orphan*/  hw_atl_rpfl2multicast_flr_en_set (struct aq_hw_s*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpfl2promiscuous_mode_en_set (struct aq_hw_s*,scalar_t__) ; 

__attribute__((used)) static int hw_atl_a0_hw_packet_filter_set(struct aq_hw_s *self,
					  unsigned int packet_filter)
{
	unsigned int i = 0U;

	hw_atl_rpfl2promiscuous_mode_en_set(self,
					    IS_FILTER_ENABLED(IFF_PROMISC));
	hw_atl_rpfl2multicast_flr_en_set(self,
					 IS_FILTER_ENABLED(IFF_MULTICAST), 0);
	hw_atl_rpfl2broadcast_en_set(self, IS_FILTER_ENABLED(IFF_BROADCAST));

	self->aq_nic_cfg->is_mc_list_enabled =
			IS_FILTER_ENABLED(IFF_MULTICAST);

	for (i = HW_ATL_A0_MAC_MIN; i < HW_ATL_A0_MAC_MAX; ++i)
		hw_atl_rpfl2_uc_flr_en_set(self,
					   (self->aq_nic_cfg->is_mc_list_enabled &&
					   (i <= self->aq_nic_cfg->mc_list_count)) ?
					   1U : 0U, i);

	return aq_hw_err_from_flags(self);
}