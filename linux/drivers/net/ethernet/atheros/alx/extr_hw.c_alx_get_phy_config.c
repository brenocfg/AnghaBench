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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct alx_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_DRV ; 
 int /*<<< orphan*/  ALX_DRV_PHY ; 
 scalar_t__ ALX_DRV_PHY_UNKNOWN ; 
 scalar_t__ ALX_GET_FIELD (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALX_MII_DBG_ADDR ; 
 int /*<<< orphan*/  ALX_PHY_CTRL ; 
 scalar_t__ ALX_PHY_CTRL_DSPRST_OUT ; 
 scalar_t__ ALX_PHY_INITED ; 
 scalar_t__ alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_read_phy_reg (struct alx_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static u16 alx_get_phy_config(struct alx_hw *hw)
{
	u32 val;
	u16 phy_val;

	val = alx_read_mem32(hw, ALX_PHY_CTRL);
	/* phy in reset */
	if ((val & ALX_PHY_CTRL_DSPRST_OUT) == 0)
		return ALX_DRV_PHY_UNKNOWN;

	val = alx_read_mem32(hw, ALX_DRV);
	val = ALX_GET_FIELD(val, ALX_DRV_PHY);
	if (ALX_DRV_PHY_UNKNOWN == val)
		return ALX_DRV_PHY_UNKNOWN;

	alx_read_phy_reg(hw, ALX_MII_DBG_ADDR, &phy_val);
	if (ALX_PHY_INITED == phy_val)
		return val;

	return ALX_DRV_PHY_UNKNOWN;
}