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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct atl1e_hw {int /*<<< orphan*/ * perm_mac_addr; } ;

/* Variables and functions */
 int AT_ERR_EEPROM ; 
 int AT_ERR_TIMEOUT ; 
 scalar_t__ AT_READ_REG (struct atl1e_hw*,scalar_t__) ; 
 scalar_t__ AT_TWSI_EEPROM_TIMEOUT ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,scalar_t__,scalar_t__) ; 
 int ETH_ALEN ; 
 scalar_t__ REG_MAC_STA_ADDR ; 
 scalar_t__ REG_TWSI_CTRL ; 
 scalar_t__ TWSI_CTRL_SW_LDSTART ; 
 int /*<<< orphan*/  atl1e_check_eeprom_exist (struct atl1e_hw*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  swab16 (int /*<<< orphan*/ ) ; 
 scalar_t__ swab32 (scalar_t__) ; 

__attribute__((used)) static int atl1e_get_permanent_address(struct atl1e_hw *hw)
{
	u32 addr[2];
	u32 i;
	u32 twsi_ctrl_data;
	u8  eth_addr[ETH_ALEN];

	if (is_valid_ether_addr(hw->perm_mac_addr))
		return 0;

	/* init */
	addr[0] = addr[1] = 0;

	if (!atl1e_check_eeprom_exist(hw)) {
		/* eeprom exist */
		twsi_ctrl_data = AT_READ_REG(hw, REG_TWSI_CTRL);
		twsi_ctrl_data |= TWSI_CTRL_SW_LDSTART;
		AT_WRITE_REG(hw, REG_TWSI_CTRL, twsi_ctrl_data);
		for (i = 0; i < AT_TWSI_EEPROM_TIMEOUT; i++) {
			msleep(10);
			twsi_ctrl_data = AT_READ_REG(hw, REG_TWSI_CTRL);
			if ((twsi_ctrl_data & TWSI_CTRL_SW_LDSTART) == 0)
				break;
		}
		if (i >= AT_TWSI_EEPROM_TIMEOUT)
			return AT_ERR_TIMEOUT;
	}

	/* maybe MAC-address is from BIOS */
	addr[0] = AT_READ_REG(hw, REG_MAC_STA_ADDR);
	addr[1] = AT_READ_REG(hw, REG_MAC_STA_ADDR + 4);
	*(u32 *) &eth_addr[2] = swab32(addr[0]);
	*(u16 *) &eth_addr[0] = swab16(*(u16 *)&addr[1]);

	if (is_valid_ether_addr(eth_addr)) {
		memcpy(hw->perm_mac_addr, eth_addr, ETH_ALEN);
		return 0;
	}

	return AT_ERR_EEPROM;
}