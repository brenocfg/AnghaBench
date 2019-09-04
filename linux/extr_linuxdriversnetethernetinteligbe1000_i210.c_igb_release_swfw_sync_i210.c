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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SW_FW_SYNC ; 
 scalar_t__ igb_get_hw_semaphore_i210 (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_put_hw_semaphore (struct e1000_hw*) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void igb_release_swfw_sync_i210(struct e1000_hw *hw, u16 mask)
{
	u32 swfw_sync;

	while (igb_get_hw_semaphore_i210(hw))
		; /* Empty */

	swfw_sync = rd32(E1000_SW_FW_SYNC);
	swfw_sync &= ~mask;
	wr32(E1000_SW_FW_SYNC, swfw_sync);

	igb_put_hw_semaphore(hw);
}