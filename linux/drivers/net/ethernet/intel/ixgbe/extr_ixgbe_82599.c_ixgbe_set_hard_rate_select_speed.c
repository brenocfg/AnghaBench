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
typedef  int u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ESDP ; 
 int IXGBE_ESDP_SDP5 ; 
 int IXGBE_ESDP_SDP5_DIR ; 
#define  IXGBE_LINK_SPEED_10GB_FULL 129 
#define  IXGBE_LINK_SPEED_1GB_FULL 128 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 

__attribute__((used)) static void
ixgbe_set_hard_rate_select_speed(struct ixgbe_hw *hw, ixgbe_link_speed speed)
{
	u32 esdp_reg = IXGBE_READ_REG(hw, IXGBE_ESDP);

	switch (speed) {
	case IXGBE_LINK_SPEED_10GB_FULL:
		esdp_reg |= (IXGBE_ESDP_SDP5_DIR | IXGBE_ESDP_SDP5);
		break;
	case IXGBE_LINK_SPEED_1GB_FULL:
		esdp_reg &= ~IXGBE_ESDP_SDP5;
		esdp_reg |= IXGBE_ESDP_SDP5_DIR;
		break;
	default:
		hw_dbg(hw, "Invalid fixed module speed\n");
		return;
	}

	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp_reg);
	IXGBE_WRITE_FLUSH(hw);
}