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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ sfp_type; } ;
struct ixgbe_hw {TYPE_1__ phy; } ;

/* Variables and functions */
 scalar_t__ IXGBE_I2C_EEPROM_DEV_ADDR ; 
 scalar_t__ IXGBE_SFF_IDENTIFIER ; 
 scalar_t__ ixgbe_sfp_type_not_present ; 

__attribute__((used)) static bool ixgbe_is_sfp_probe(struct ixgbe_hw *hw, u8 offset, u8 addr)
{
	if (addr == IXGBE_I2C_EEPROM_DEV_ADDR &&
	    offset == IXGBE_SFF_IDENTIFIER &&
	    hw->phy.sfp_type == ixgbe_sfp_type_not_present)
		return true;
	return false;
}