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
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

inline void i40iw_wr32(struct i40iw_hw *hw, u32 reg, u32 value)
{
	writel(value, hw->hw_addr + reg);
}