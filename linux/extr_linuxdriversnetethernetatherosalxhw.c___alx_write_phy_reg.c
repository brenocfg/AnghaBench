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
typedef  int /*<<< orphan*/  u16 ;
struct alx_hw {int dummy; } ;

/* Variables and functions */
 int alx_write_phy_core (struct alx_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __alx_write_phy_reg(struct alx_hw *hw, u16 reg, u16 phy_data)
{
	return alx_write_phy_core(hw, false, 0, reg, phy_data);
}