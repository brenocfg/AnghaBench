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
typedef  int u32 ;
typedef  int u16 ;
struct i40e_hw {int flags; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_AQ_PHY_REG_ACCESS_EXTERNAL ; 
 int I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE ; 
 int /*<<< orphan*/  I40E_PFGEN_PORTNUM ; 
 int I40E_PFGEN_PORTNUM_PORT_NUM_MASK ; 
 int /*<<< orphan*/  I40E_PHY_COM_REG_PAGE ; 
 int I40E_PHY_LED_LINK_MODE_MASK ; 
 int I40E_PHY_LED_PROV_REG_1 ; 
 scalar_t__ I40E_SUCCESS ; 
 scalar_t__ i40e_aq_get_phy_register (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_get_phy_address (struct i40e_hw*,scalar_t__) ; 
 scalar_t__ i40e_read_phy_register_clause45 (struct i40e_hw*,int /*<<< orphan*/ ,int,scalar_t__,int*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

i40e_status i40e_led_get_phy(struct i40e_hw *hw, u16 *led_addr,
			     u16 *val)
{
	i40e_status status = 0;
	u16 gpio_led_port;
	u8 phy_addr = 0;
	u16 reg_val;
	u16 temp_addr;
	u8 port_num;
	u32 i;
	u32 reg_val_aq;

	if (hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE) {
		status =
		      i40e_aq_get_phy_register(hw,
					       I40E_AQ_PHY_REG_ACCESS_EXTERNAL,
					       I40E_PHY_COM_REG_PAGE,
					       I40E_PHY_LED_PROV_REG_1,
					       &reg_val_aq, NULL);
		if (status == I40E_SUCCESS)
			*val = (u16)reg_val_aq;
		return status;
	}
	temp_addr = I40E_PHY_LED_PROV_REG_1;
	i = rd32(hw, I40E_PFGEN_PORTNUM);
	port_num = (u8)(i & I40E_PFGEN_PORTNUM_PORT_NUM_MASK);
	phy_addr = i40e_get_phy_address(hw, port_num);

	for (gpio_led_port = 0; gpio_led_port < 3; gpio_led_port++,
	     temp_addr++) {
		status = i40e_read_phy_register_clause45(hw,
							 I40E_PHY_COM_REG_PAGE,
							 temp_addr, phy_addr,
							 &reg_val);
		if (status)
			return status;
		*val = reg_val;
		if (reg_val & I40E_PHY_LED_LINK_MODE_MASK) {
			*led_addr = temp_addr;
			break;
		}
	}
	return status;
}