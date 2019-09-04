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
struct ixgb_hw {scalar_t__ eeprom; } ;
struct ixgb_ee_map_type {int /*<<< orphan*/ * mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int ETH_ALEN ; 
 scalar_t__ ixgb_check_and_get_eeprom_data (struct ixgb_hw*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ *) ; 

void
ixgb_get_ee_mac_addr(struct ixgb_hw *hw,
			u8 *mac_addr)
{
	int i;
	struct ixgb_ee_map_type *ee_map = (struct ixgb_ee_map_type *)hw->eeprom;

	ENTER();

	if (ixgb_check_and_get_eeprom_data(hw)) {
		for (i = 0; i < ETH_ALEN; i++) {
			mac_addr[i] = ee_map->mac_addr[i];
		}
		pr_debug("eeprom mac address = %pM\n", mac_addr);
	}
}