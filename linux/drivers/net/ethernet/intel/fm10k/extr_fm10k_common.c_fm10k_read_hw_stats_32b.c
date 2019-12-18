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
struct fm10k_hw_stat {scalar_t__ base_h; scalar_t__ base_l; } ;
struct fm10k_hw {int /*<<< orphan*/  hw_addr; } ;

/* Variables and functions */
 scalar_t__ FM10K_REMOVED (int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_read_reg (struct fm10k_hw*,scalar_t__) ; 

u32 fm10k_read_hw_stats_32b(struct fm10k_hw *hw, u32 addr,
			    struct fm10k_hw_stat *stat)
{
	u32 delta = fm10k_read_reg(hw, addr) - stat->base_l;

	if (FM10K_REMOVED(hw->hw_addr))
		stat->base_h = 0;

	return delta;
}