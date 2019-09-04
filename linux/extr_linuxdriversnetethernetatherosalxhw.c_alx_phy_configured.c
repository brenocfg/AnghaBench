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
struct alx_hw {int /*<<< orphan*/  adv_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_DRV_PHY ; 
 scalar_t__ ALX_DRV_PHY_UNKNOWN ; 
 scalar_t__ ALX_GET_FIELD (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ alx_get_phy_config (struct alx_hw*) ; 
 scalar_t__ ethadv_to_hw_cfg (struct alx_hw*,int /*<<< orphan*/ ) ; 

bool alx_phy_configured(struct alx_hw *hw)
{
	u32 cfg, hw_cfg;

	cfg = ethadv_to_hw_cfg(hw, hw->adv_cfg);
	cfg = ALX_GET_FIELD(cfg, ALX_DRV_PHY);
	hw_cfg = alx_get_phy_config(hw);

	if (hw_cfg == ALX_DRV_PHY_UNKNOWN)
		return false;

	return cfg == hw_cfg;
}