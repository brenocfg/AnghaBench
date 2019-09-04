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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {scalar_t__ device_id; TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_DEV_ID_82598AT2 ; 
 int /*<<< orphan*/  IXGBE_ERR_LINK_SETUP ; 
 scalar_t__ IXGBE_VALIDATE_LINK_READY_TIMEOUT ; 
 int MDIO_AN_STAT1_COMPLETE ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int MDIO_STAT1_LSTATUS ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static s32 ixgbe_validate_link_ready(struct ixgbe_hw *hw)
{
	u32 timeout;
	u16 an_reg;

	if (hw->device_id != IXGBE_DEV_ID_82598AT2)
		return 0;

	for (timeout = 0;
	     timeout < IXGBE_VALIDATE_LINK_READY_TIMEOUT; timeout++) {
		hw->phy.ops.read_reg(hw, MDIO_STAT1, MDIO_MMD_AN, &an_reg);

		if ((an_reg & MDIO_AN_STAT1_COMPLETE) &&
		    (an_reg & MDIO_STAT1_LSTATUS))
			break;

		msleep(100);
	}

	if (timeout == IXGBE_VALIDATE_LINK_READY_TIMEOUT) {
		hw_dbg(hw, "Link was indicated but link is down\n");
		return IXGBE_ERR_LINK_SETUP;
	}

	return 0;
}