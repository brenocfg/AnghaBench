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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct igc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_SW_FW_SYNC ; 
 scalar_t__ igc_get_hw_semaphore_i225 (struct igc_hw*) ; 
 int /*<<< orphan*/  igc_put_hw_semaphore (struct igc_hw*) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void igc_release_swfw_sync_i225(struct igc_hw *hw, u16 mask)
{
	u32 swfw_sync;

	while (igc_get_hw_semaphore_i225(hw))
		; /* Empty */

	swfw_sync = rd32(IGC_SW_FW_SYNC);
	swfw_sync &= ~mask;
	wr32(IGC_SW_FW_SYNC, swfw_sync);

	igc_put_hw_semaphore(hw);
}