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
typedef  int u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_RXDCTL_RLPML_EN ; 
 int /*<<< orphan*/  IXGBE_VFRXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbevf_hv_set_rlpml_vf(struct ixgbe_hw *hw, u16 max_size)
{
	u32 reg;

	/* If we are on Hyper-V, we implement this functionality
	 * differently.
	 */
	reg =  IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(0));
	/* CRC == 4 */
	reg |= ((max_size + 4) | IXGBE_RXDCTL_RLPML_EN);
	IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(0), reg);

	return 0;
}