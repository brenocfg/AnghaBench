#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {scalar_t__ device_id; TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_DEV_ID_82599_T3_LOM ; 
 int /*<<< orphan*/  IXGBE_ERR_OVERTEMP ; 
 int /*<<< orphan*/  IXGBE_TN_LASI_STATUS_REG ; 
 int IXGBE_TN_LASI_STATUS_TEMP_ALARM ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

s32 ixgbe_tn_check_overtemp(struct ixgbe_hw *hw)
{
	u16 phy_data = 0;

	if (hw->device_id != IXGBE_DEV_ID_82599_T3_LOM)
		return 0;

	/* Check that the LASI temp alarm status was triggered */
	hw->phy.ops.read_reg(hw, IXGBE_TN_LASI_STATUS_REG,
			     MDIO_MMD_PMAPMD, &phy_data);

	if (!(phy_data & IXGBE_TN_LASI_STATUS_TEMP_ALARM))
		return 0;

	return IXGBE_ERR_OVERTEMP;
}