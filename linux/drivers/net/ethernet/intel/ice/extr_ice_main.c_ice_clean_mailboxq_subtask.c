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
struct ice_hw {int /*<<< orphan*/  mailboxq; } ;
struct ice_pf {int /*<<< orphan*/  state; struct ice_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_CTL_Q_MAILBOX ; 
 int /*<<< orphan*/  __ICE_MAILBOXQ_EVENT_PENDING ; 
 scalar_t__ __ice_clean_ctrlq (struct ice_pf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_ctrlq_pending (struct ice_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_clean_mailboxq_subtask(struct ice_pf *pf)
{
	struct ice_hw *hw = &pf->hw;

	if (!test_bit(__ICE_MAILBOXQ_EVENT_PENDING, pf->state))
		return;

	if (__ice_clean_ctrlq(pf, ICE_CTL_Q_MAILBOX))
		return;

	clear_bit(__ICE_MAILBOXQ_EVENT_PENDING, pf->state);

	if (ice_ctrlq_pending(hw, &hw->mailboxq))
		__ice_clean_ctrlq(pf, ICE_CTL_Q_MAILBOX);

	ice_flush(hw);
}