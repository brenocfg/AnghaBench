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
typedef  int u32 ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {int latch_event_flags; int /*<<< orphan*/ * latch_events; struct i40e_hw hw; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  I40E_PRTTSYN_STAT_1 ; 
 int /*<<< orphan*/  jiffies ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 i40e_ptp_get_rx_events(struct i40e_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	u32 prttsyn_stat, new_latch_events;
	int  i;

	prttsyn_stat = rd32(hw, I40E_PRTTSYN_STAT_1);
	new_latch_events = prttsyn_stat & ~pf->latch_event_flags;

	/* Update the jiffies time for any newly latched timestamp. This
	 * ensures that we store the time that we first discovered a timestamp
	 * was latched by the hardware. The service task will later determine
	 * if we should free the latch and drop that timestamp should too much
	 * time pass. This flow ensures that we only update jiffies for new
	 * events latched since the last time we checked, and not all events
	 * currently latched, so that the service task accounting remains
	 * accurate.
	 */
	for (i = 0; i < 4; i++) {
		if (new_latch_events & BIT(i))
			pf->latch_events[i] = jiffies;
	}

	/* Finally, we store the current status of the Rx timestamp latches */
	pf->latch_event_flags = prttsyn_stat;

	return prttsyn_stat;
}