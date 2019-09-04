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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 int BROADCAST_STORM_RATE ; 
 int BROADCAST_STORM_RATE_HI ; 
 int BROADCAST_STORM_RATE_LO ; 
 scalar_t__ BROADCAST_STORM_VALUE ; 
 scalar_t__ KS8842_SWITCH_CTRL_3_OFFSET ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void sw_cfg_broad_storm(struct ksz_hw *hw, u8 percent)
{
	u16 data;
	u32 value = ((u32) BROADCAST_STORM_VALUE * (u32) percent / 100);

	if (value > BROADCAST_STORM_RATE)
		value = BROADCAST_STORM_RATE;

	data = readw(hw->io + KS8842_SWITCH_CTRL_3_OFFSET);
	data &= ~(BROADCAST_STORM_RATE_LO | BROADCAST_STORM_RATE_HI);
	data |= ((value & 0x00FF) << 8) | ((value & 0xFF00) >> 8);
	writew(data, hw->io + KS8842_SWITCH_CTRL_3_OFFSET);
}