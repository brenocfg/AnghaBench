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
typedef  int u16 ;
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 int BROADCAST_STORM_RATE_HI ; 
 int BROADCAST_STORM_RATE_LO ; 
 int /*<<< orphan*/  BROADCAST_STORM_VALUE ; 
 int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 scalar_t__ KS8842_SWITCH_CTRL_3_OFFSET ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static void sw_get_broad_storm(struct ksz_hw *hw, u8 *percent)
{
	int num;
	u16 data;

	data = readw(hw->io + KS8842_SWITCH_CTRL_3_OFFSET);
	num = (data & BROADCAST_STORM_RATE_HI);
	num <<= 8;
	num |= (data & BROADCAST_STORM_RATE_LO) >> 8;
	num = DIV_ROUND_CLOSEST(num * 100, BROADCAST_STORM_VALUE);
	*percent = (u8) num;
}