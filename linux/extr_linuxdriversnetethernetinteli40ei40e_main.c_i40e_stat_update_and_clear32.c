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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ rd32 (struct i40e_hw*,scalar_t__) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,scalar_t__,int) ; 

__attribute__((used)) static void i40e_stat_update_and_clear32(struct i40e_hw *hw, u32 reg, u64 *stat)
{
	u32 new_data = rd32(hw, reg);

	wr32(hw, reg, 1); /* must write a nonzero value to clear register */
	*stat += new_data;
}