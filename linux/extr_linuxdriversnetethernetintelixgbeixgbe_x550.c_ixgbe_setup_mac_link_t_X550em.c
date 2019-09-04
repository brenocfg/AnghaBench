#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ (* setup_link_speed ) (struct ixgbe_hw*,int,int) ;} ;
struct TYPE_6__ {int nw_mng_if_sel; TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_NW_MNG_IF_SEL_INT_PHY_MODE ; 
 scalar_t__ ixgbe_mac_X550EM_x ; 
 scalar_t__ ixgbe_setup_ixfi_x550em (struct ixgbe_hw*,int*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int,int) ; 

__attribute__((used)) static s32 ixgbe_setup_mac_link_t_X550em(struct ixgbe_hw *hw,
					 ixgbe_link_speed speed,
					 bool autoneg_wait)
{
	s32 status;
	ixgbe_link_speed force_speed;

	/* Setup internal/external PHY link speed to iXFI (10G), unless
	 * only 1G is auto advertised then setup KX link.
	 */
	if (speed & IXGBE_LINK_SPEED_10GB_FULL)
		force_speed = IXGBE_LINK_SPEED_10GB_FULL;
	else
		force_speed = IXGBE_LINK_SPEED_1GB_FULL;

	/* If X552 and internal link mode is XFI, then setup XFI internal link.
	 */
	if (hw->mac.type == ixgbe_mac_X550EM_x &&
	    !(hw->phy.nw_mng_if_sel & IXGBE_NW_MNG_IF_SEL_INT_PHY_MODE)) {
		status = ixgbe_setup_ixfi_x550em(hw, &force_speed);

		if (status)
			return status;
	}

	return hw->phy.ops.setup_link_speed(hw, speed, autoneg_wait);
}