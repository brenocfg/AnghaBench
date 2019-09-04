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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_MMDAAD ; 
 int /*<<< orphan*/  E1000_MMDAC ; 
 int E1000_MMDAC_FUNC_DATA ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 __igb_access_xmdio_reg(struct e1000_hw *hw, u16 address,
				  u8 dev_addr, u16 *data, bool read)
{
	s32 ret_val = 0;

	ret_val = hw->phy.ops.write_reg(hw, E1000_MMDAC, dev_addr);
	if (ret_val)
		return ret_val;

	ret_val = hw->phy.ops.write_reg(hw, E1000_MMDAAD, address);
	if (ret_val)
		return ret_val;

	ret_val = hw->phy.ops.write_reg(hw, E1000_MMDAC, E1000_MMDAC_FUNC_DATA |
							 dev_addr);
	if (ret_val)
		return ret_val;

	if (read)
		ret_val = hw->phy.ops.read_reg(hw, E1000_MMDAAD, data);
	else
		ret_val = hw->phy.ops.write_reg(hw, E1000_MMDAAD, *data);
	if (ret_val)
		return ret_val;

	/* Recalibrate the device back to 0 */
	ret_val = hw->phy.ops.write_reg(hw, E1000_MMDAC, 0);
	if (ret_val)
		return ret_val;

	return ret_val;
}