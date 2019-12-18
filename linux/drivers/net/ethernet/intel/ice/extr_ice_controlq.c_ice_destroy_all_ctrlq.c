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
struct ice_hw {int /*<<< orphan*/  mailboxq; int /*<<< orphan*/  adminq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ice_destroy_ctrlq_locks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_shutdown_all_ctrlq (struct ice_hw*) ; 

void ice_destroy_all_ctrlq(struct ice_hw *hw)
{
	/* shut down all the control queues first */
	ice_shutdown_all_ctrlq(hw);

	ice_destroy_ctrlq_locks(&hw->adminq);
	ice_destroy_ctrlq_locks(&hw->mailboxq);
}