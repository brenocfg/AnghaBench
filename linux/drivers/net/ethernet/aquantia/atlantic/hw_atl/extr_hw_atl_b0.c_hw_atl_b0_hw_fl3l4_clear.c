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
struct aq_rx_filter_l3l4 {int /*<<< orphan*/  is_ipv6; scalar_t__ location; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int HW_ATL_RX_CNT_REG_ADDR_IPV6 ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rpf_l4_dpd_set (struct aq_hw_s*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  hw_atl_rpf_l4_spd_set (struct aq_hw_s*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  hw_atl_rpfl3l4_cmd_clear (struct aq_hw_s*,scalar_t__) ; 
 int /*<<< orphan*/  hw_atl_rpfl3l4_ipv4_dest_addr_clear (struct aq_hw_s*,scalar_t__) ; 
 int /*<<< orphan*/  hw_atl_rpfl3l4_ipv4_src_addr_clear (struct aq_hw_s*,scalar_t__) ; 
 int /*<<< orphan*/  hw_atl_rpfl3l4_ipv6_dest_addr_clear (struct aq_hw_s*,scalar_t__) ; 
 int /*<<< orphan*/  hw_atl_rpfl3l4_ipv6_src_addr_clear (struct aq_hw_s*,scalar_t__) ; 

__attribute__((used)) static int hw_atl_b0_hw_fl3l4_clear(struct aq_hw_s *self,
				    struct aq_rx_filter_l3l4 *data)
{
	u8 location = data->location;

	if (!data->is_ipv6) {
		hw_atl_rpfl3l4_cmd_clear(self, location);
		hw_atl_rpf_l4_spd_set(self, 0U, location);
		hw_atl_rpf_l4_dpd_set(self, 0U, location);
		hw_atl_rpfl3l4_ipv4_src_addr_clear(self, location);
		hw_atl_rpfl3l4_ipv4_dest_addr_clear(self, location);
	} else {
		int i;

		for (i = 0; i < HW_ATL_RX_CNT_REG_ADDR_IPV6; ++i) {
			hw_atl_rpfl3l4_cmd_clear(self, location + i);
			hw_atl_rpf_l4_spd_set(self, 0U, location + i);
			hw_atl_rpf_l4_dpd_set(self, 0U, location + i);
		}
		hw_atl_rpfl3l4_ipv6_src_addr_clear(self, location);
		hw_atl_rpfl3l4_ipv6_dest_addr_clear(self, location);
	}

	return aq_hw_err_from_flags(self);
}