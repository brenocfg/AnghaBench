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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct alx_hw {int dummy; } ;

/* Variables and functions */
 int alx_read_phy_core (struct alx_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __alx_read_phy_ext(struct alx_hw *hw, u8 dev, u16 reg, u16 *pdata)
{
	return alx_read_phy_core(hw, true, dev, reg, pdata);
}