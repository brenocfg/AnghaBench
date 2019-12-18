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
struct ice_hw {int /*<<< orphan*/  adminq; } ;
struct ice_pf {int /*<<< orphan*/  state; struct ice_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_CTL_Q_ADMIN ; 
 int /*<<< orphan*/  __ICE_ADMINQ_EVENT_PENDING ; 
 scalar_t__ __ice_clean_ctrlq (struct ice_pf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_ctrlq_pending (struct ice_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_clean_adminq_subtask(struct ice_pf *pf)
{
	struct ice_hw *hw = &pf->hw;

	if (!test_bit(__ICE_ADMINQ_EVENT_PENDING, pf->state))
		return;

	if (__ice_clean_ctrlq(pf, ICE_CTL_Q_ADMIN))
		return;

	clear_bit(__ICE_ADMINQ_EVENT_PENDING, pf->state);

	/* There might be a situation where new messages arrive to a control
	 * queue between processing the last message and clearing the
	 * EVENT_PENDING bit. So before exiting, check queue head again (using
	 * ice_ctrlq_pending) and process new messages if any.
	 */
	if (ice_ctrlq_pending(hw, &hw->adminq))
		__ice_clean_ctrlq(pf, ICE_CTL_Q_ADMIN);

	ice_flush(hw);
}