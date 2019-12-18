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
 int /*<<< orphan*/  IXGBE_HW_READ_REG ; 
 int IXGBE_MDIO_COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  IXGBE_MSCA ; 
 int IXGBE_MSCA_MDI_COMMAND ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readx_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static s32 ixgbe_msca_cmd(struct ixgbe_hw *hw, u32 cmd)
{
	IXGBE_WRITE_REG(hw, IXGBE_MSCA, cmd);

	return readx_poll_timeout(IXGBE_HW_READ_REG, IXGBE_MSCA, cmd,
				  !(cmd & IXGBE_MSCA_MDI_COMMAND), 10,
				  10 * IXGBE_MDIO_COMMAND_TIMEOUT);
}