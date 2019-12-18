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
struct igc_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_CTRL ; 
 int IGC_CTRL_FRCDPX ; 
 int IGC_CTRL_FRCSPD ; 
 int IGC_CTRL_SLU ; 
 int /*<<< orphan*/  igc_setup_copper_link (struct igc_hw*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 igc_setup_copper_link_base(struct igc_hw *hw)
{
	s32  ret_val = 0;
	u32 ctrl;

	ctrl = rd32(IGC_CTRL);
	ctrl |= IGC_CTRL_SLU;
	ctrl &= ~(IGC_CTRL_FRCSPD | IGC_CTRL_FRCDPX);
	wr32(IGC_CTRL, ctrl);

	ret_val = igc_setup_copper_link(hw);

	return ret_val;
}