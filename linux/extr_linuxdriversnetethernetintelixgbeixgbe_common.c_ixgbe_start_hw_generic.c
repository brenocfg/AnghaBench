#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_device_caps ) (struct ixgbe_hw*,int*) ;scalar_t__ (* setup_fc ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* clear_hw_cntrs ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* clear_vfta ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* get_media_type ) (struct ixgbe_hw*) ;} ;
struct TYPE_8__ {int type; TYPE_3__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* identify ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {TYPE_1__ ops; int /*<<< orphan*/  media_type; } ;
struct ixgbe_hw {int need_crosstalk_fix; int adapter_stopped; TYPE_4__ mac; TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_CTRL_EXT ; 
 int /*<<< orphan*/  IXGBE_CTRL_EXT_NS_DIS ; 
 int IXGBE_DEVICE_CAPS_NO_CROSSTALK_WR ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ixgbe_mac_82599EB 130 
#define  ixgbe_mac_X550EM_x 129 
#define  ixgbe_mac_x550em_a 128 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*) ; 
 scalar_t__ stub5 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub6 (struct ixgbe_hw*,int*) ; 

s32 ixgbe_start_hw_generic(struct ixgbe_hw *hw)
{
	s32 ret_val;
	u32 ctrl_ext;
	u16 device_caps;

	/* Set the media type */
	hw->phy.media_type = hw->mac.ops.get_media_type(hw);

	/* Identify the PHY */
	hw->phy.ops.identify(hw);

	/* Clear the VLAN filter table */
	hw->mac.ops.clear_vfta(hw);

	/* Clear statistics registers */
	hw->mac.ops.clear_hw_cntrs(hw);

	/* Set No Snoop Disable */
	ctrl_ext = IXGBE_READ_REG(hw, IXGBE_CTRL_EXT);
	ctrl_ext |= IXGBE_CTRL_EXT_NS_DIS;
	IXGBE_WRITE_REG(hw, IXGBE_CTRL_EXT, ctrl_ext);
	IXGBE_WRITE_FLUSH(hw);

	/* Setup flow control if method for doing so */
	if (hw->mac.ops.setup_fc) {
		ret_val = hw->mac.ops.setup_fc(hw);
		if (ret_val)
			return ret_val;
	}

	/* Cashe bit indicating need for crosstalk fix */
	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		hw->mac.ops.get_device_caps(hw, &device_caps);
		if (device_caps & IXGBE_DEVICE_CAPS_NO_CROSSTALK_WR)
			hw->need_crosstalk_fix = false;
		else
			hw->need_crosstalk_fix = true;
		break;
	default:
		hw->need_crosstalk_fix = false;
		break;
	}

	/* Clear adapter stopped flag */
	hw->adapter_stopped = false;

	return 0;
}