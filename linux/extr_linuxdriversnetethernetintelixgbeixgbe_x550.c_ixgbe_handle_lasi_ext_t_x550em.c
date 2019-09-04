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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ (* setup_internal_link ) (struct ixgbe_hw*) ;} ;
struct ixgbe_phy_info {TYPE_1__ ops; } ;
struct ixgbe_hw {struct ixgbe_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ ixgbe_get_lasi_ext_t_x550em (struct ixgbe_hw*,int*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_handle_lasi_ext_t_x550em(struct ixgbe_hw *hw)
{
	struct ixgbe_phy_info *phy = &hw->phy;
	bool lsc;
	u32 status;

	status = ixgbe_get_lasi_ext_t_x550em(hw, &lsc);
	if (status)
		return status;

	if (lsc && phy->ops.setup_internal_link)
		return phy->ops.setup_internal_link(hw);

	return 0;
}