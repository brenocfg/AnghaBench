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
struct TYPE_5__ {int /*<<< orphan*/  (* get_media_type ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {int type; TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;

/* Variables and functions */
#define  ixgbe_mac_82598EB 133 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X550EM_x 131 
#define  ixgbe_mac_x550em_a 130 
#define  ixgbe_media_type_fiber 129 
#define  ixgbe_media_type_fiber_qsfp 128 
 int /*<<< orphan*/  ixgbe_phy_nl ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static inline bool ixgbe_is_sfp(struct ixgbe_hw *hw)
{
	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		if (hw->phy.type == ixgbe_phy_nl)
			return true;
		return false;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		switch (hw->mac.ops.get_media_type(hw)) {
		case ixgbe_media_type_fiber:
		case ixgbe_media_type_fiber_qsfp:
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}