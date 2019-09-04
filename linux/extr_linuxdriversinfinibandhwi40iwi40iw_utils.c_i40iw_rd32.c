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
typedef  scalar_t__ u32 ;
struct i40iw_hw {scalar_t__ hw_addr; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 

inline u32 i40iw_rd32(struct i40iw_hw *hw, u32 reg)
{
	return readl(hw->hw_addr + reg);
}