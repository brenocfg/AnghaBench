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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_FDIR_CMD_INCOMPLETE ; 
 int /*<<< orphan*/  IXGBE_FDIRCMD ; 
 int IXGBE_FDIRCMD_CMD_MASK ; 
 int IXGBE_FDIRCMD_CMD_POLL ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 ixgbe_fdir_check_cmd_complete(struct ixgbe_hw *hw, u32 *fdircmd)
{
	int i;

	for (i = 0; i < IXGBE_FDIRCMD_CMD_POLL; i++) {
		*fdircmd = IXGBE_READ_REG(hw, IXGBE_FDIRCMD);
		if (!(*fdircmd & IXGBE_FDIRCMD_CMD_MASK))
			return 0;
		udelay(10);
	}

	return IXGBE_ERR_FDIR_CMD_INCOMPLETE;
}