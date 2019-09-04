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
typedef  int u8 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HW_ATL_B0_MAC ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rpfl2_uc_flr_en_set (struct aq_hw_s*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpfl2unicast_dest_addresslsw_set (struct aq_hw_s*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpfl2unicast_dest_addressmsw_set (struct aq_hw_s*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_atl_b0_hw_mac_addr_set(struct aq_hw_s *self, u8 *mac_addr)
{
	int err = 0;
	unsigned int h = 0U;
	unsigned int l = 0U;

	if (!mac_addr) {
		err = -EINVAL;
		goto err_exit;
	}
	h = (mac_addr[0] << 8) | (mac_addr[1]);
	l = (mac_addr[2] << 24) | (mac_addr[3] << 16) |
		(mac_addr[4] << 8) | mac_addr[5];

	hw_atl_rpfl2_uc_flr_en_set(self, 0U, HW_ATL_B0_MAC);
	hw_atl_rpfl2unicast_dest_addresslsw_set(self, l, HW_ATL_B0_MAC);
	hw_atl_rpfl2unicast_dest_addressmsw_set(self, h, HW_ATL_B0_MAC);
	hw_atl_rpfl2_uc_flr_en_set(self, 1U, HW_ATL_B0_MAC);

	err = aq_hw_err_from_flags(self);

err_exit:
	return err;
}