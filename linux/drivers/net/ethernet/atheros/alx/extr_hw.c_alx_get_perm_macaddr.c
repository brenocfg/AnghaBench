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
typedef  int u32 ;
struct alx_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_EFLD ; 
 int ALX_EFLD_E_EXIST ; 
 int ALX_EFLD_F_EXIST ; 
 int ALX_EFLD_START ; 
 int ALX_EFLD_STAT ; 
 int /*<<< orphan*/  ALX_SLD ; 
 int ALX_SLD_START ; 
 int ALX_SLD_STAT ; 
 int EIO ; 
 scalar_t__ alx_read_macaddr (struct alx_hw*,int /*<<< orphan*/ *) ; 
 int alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_wait_reg (struct alx_hw*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int) ; 

int alx_get_perm_macaddr(struct alx_hw *hw, u8 *addr)
{
	u32 val;

	/* try to get it from register first */
	if (alx_read_macaddr(hw, addr))
		return 0;

	/* try to load from efuse */
	if (!alx_wait_reg(hw, ALX_SLD, ALX_SLD_STAT | ALX_SLD_START, &val))
		return -EIO;
	alx_write_mem32(hw, ALX_SLD, val | ALX_SLD_START);
	if (!alx_wait_reg(hw, ALX_SLD, ALX_SLD_START, NULL))
		return -EIO;
	if (alx_read_macaddr(hw, addr))
		return 0;

	/* try to load from flash/eeprom (if present) */
	val = alx_read_mem32(hw, ALX_EFLD);
	if (val & (ALX_EFLD_F_EXIST | ALX_EFLD_E_EXIST)) {
		if (!alx_wait_reg(hw, ALX_EFLD,
				  ALX_EFLD_STAT | ALX_EFLD_START, &val))
			return -EIO;
		alx_write_mem32(hw, ALX_EFLD, val | ALX_EFLD_START);
		if (!alx_wait_reg(hw, ALX_EFLD, ALX_EFLD_START, NULL))
			return -EIO;
		if (alx_read_macaddr(hw, addr))
			return 0;
	}

	return -EIO;
}