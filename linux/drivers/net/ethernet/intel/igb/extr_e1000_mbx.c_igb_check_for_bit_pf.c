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
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_MBX ; 
 int /*<<< orphan*/  E1000_MBVFICR ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 igb_check_for_bit_pf(struct e1000_hw *hw, u32 mask)
{
	u32 mbvficr = rd32(E1000_MBVFICR);
	s32 ret_val = -E1000_ERR_MBX;

	if (mbvficr & mask) {
		ret_val = 0;
		wr32(E1000_MBVFICR, mask);
	}

	return ret_val;
}