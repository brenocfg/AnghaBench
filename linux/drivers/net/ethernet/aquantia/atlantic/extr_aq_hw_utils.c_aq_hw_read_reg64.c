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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int aq_hw_read_reg (struct aq_hw_s*,scalar_t__) ; 

u64 aq_hw_read_reg64(struct aq_hw_s *hw, u32 reg)
{
	u64 value = aq_hw_read_reg(hw, reg);

	value |= (u64)aq_hw_read_reg(hw, reg + 4) << 32;
	return value;
}