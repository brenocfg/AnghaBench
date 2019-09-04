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
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_aqc_mac_address_read_data {int /*<<< orphan*/  pf_lan_mac; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int I40E_AQC_LAN_ADDR_VALID ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aq_mac_address_read (struct i40e_hw*,int*,struct i40e_aqc_mac_address_read_data*,int /*<<< orphan*/ *) ; 

i40e_status i40e_get_mac_addr(struct i40e_hw *hw, u8 *mac_addr)
{
	struct i40e_aqc_mac_address_read_data addrs;
	i40e_status status;
	u16 flags = 0;

	status = i40e_aq_mac_address_read(hw, &flags, &addrs, NULL);

	if (flags & I40E_AQC_LAN_ADDR_VALID)
		ether_addr_copy(mac_addr, addrs.pf_lan_mac);

	return status;
}