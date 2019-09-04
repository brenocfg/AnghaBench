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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  __e1000_read_phy_reg_hv (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

s32 e1000_read_phy_reg_hv(struct e1000_hw *hw, u32 offset, u16 *data)
{
	return __e1000_read_phy_reg_hv(hw, offset, data, false, false);
}