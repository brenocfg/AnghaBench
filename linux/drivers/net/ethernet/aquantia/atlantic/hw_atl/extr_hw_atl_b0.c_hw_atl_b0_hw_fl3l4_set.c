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
struct aq_rx_filter_l3l4 {int /*<<< orphan*/  cmd; int /*<<< orphan*/  p_src; int /*<<< orphan*/  p_dst; int /*<<< orphan*/ * ip_src; int /*<<< orphan*/ * ip_dst; int /*<<< orphan*/  is_ipv6; int /*<<< orphan*/  location; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_b0_hw_fl3l4_clear (struct aq_hw_s*,struct aq_rx_filter_l3l4*) ; 
 int /*<<< orphan*/  hw_atl_rpf_l4_dpd_set (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpf_l4_spd_set (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpfl3l4_cmd_set (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpfl3l4_ipv4_dest_addr_set (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpfl3l4_ipv4_src_addr_set (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpfl3l4_ipv6_dest_addr_set (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_atl_rpfl3l4_ipv6_src_addr_set (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hw_atl_b0_hw_fl3l4_set(struct aq_hw_s *self,
				  struct aq_rx_filter_l3l4 *data)
{
	u8 location = data->location;

	hw_atl_b0_hw_fl3l4_clear(self, data);

	if (data->cmd) {
		if (!data->is_ipv6) {
			hw_atl_rpfl3l4_ipv4_dest_addr_set(self,
							  location,
							  data->ip_dst[0]);
			hw_atl_rpfl3l4_ipv4_src_addr_set(self,
							 location,
							 data->ip_src[0]);
		} else {
			hw_atl_rpfl3l4_ipv6_dest_addr_set(self,
							  location,
							  data->ip_dst);
			hw_atl_rpfl3l4_ipv6_src_addr_set(self,
							 location,
							 data->ip_src);
		}
	}
	hw_atl_rpf_l4_dpd_set(self, data->p_dst, location);
	hw_atl_rpf_l4_spd_set(self, data->p_src, location);
	hw_atl_rpfl3l4_cmd_set(self, location, data->cmd);

	return aq_hw_err_from_flags(self);
}