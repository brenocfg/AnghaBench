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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ice_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT_ULL (int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ rd32 (struct ice_hw*,scalar_t__) ; 

__attribute__((used)) static void ice_stat_update32(struct ice_hw *hw, u32 reg, bool prev_stat_loaded,
			      u64 *prev_stat, u64 *cur_stat)
{
	u32 new_data;

	new_data = rd32(hw, reg);

	/* device stats are not reset at PFR, they likely will not be zeroed
	 * when the driver starts. So save the first values read and use them as
	 * offsets to be subtracted from the raw values in order to report stats
	 * that count from zero.
	 */
	if (!prev_stat_loaded)
		*prev_stat = new_data;
	if (likely(new_data >= *prev_stat))
		*cur_stat = new_data - *prev_stat;
	else
		/* to manage the potential roll-over */
		*cur_stat = (new_data + BIT_ULL(32)) - *prev_stat;
}