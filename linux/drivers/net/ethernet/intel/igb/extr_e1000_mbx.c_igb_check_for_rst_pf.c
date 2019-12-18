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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  rsts; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct e1000_hw {TYPE_2__ mbx; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_ERR_MBX ; 
 int /*<<< orphan*/  E1000_VFLRE ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 igb_check_for_rst_pf(struct e1000_hw *hw, u16 vf_number)
{
	u32 vflre = rd32(E1000_VFLRE);
	s32 ret_val = -E1000_ERR_MBX;

	if (vflre & BIT(vf_number)) {
		ret_val = 0;
		wr32(E1000_VFLRE, BIT(vf_number));
		hw->mbx.stats.rsts++;
	}

	return ret_val;
}