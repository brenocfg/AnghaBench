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
struct atl1e_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_REGW (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int GPHY_CTRL_EXT_RESET ; 
 int GPHY_CTRL_PW_WOL_DIS ; 
 int /*<<< orphan*/  REG_GPHY_CTRL ; 

void atl1e_force_ps(struct atl1e_hw *hw)
{
	AT_WRITE_REGW(hw, REG_GPHY_CTRL,
			GPHY_CTRL_PW_WOL_DIS | GPHY_CTRL_EXT_RESET);
}