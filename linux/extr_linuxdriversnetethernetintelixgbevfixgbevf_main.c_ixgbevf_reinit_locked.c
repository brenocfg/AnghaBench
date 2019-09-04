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
struct ixgbevf_adapter {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGBEVF_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  ixgbevf_down (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_up (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ixgbevf_reinit_locked(struct ixgbevf_adapter *adapter)
{
	WARN_ON(in_interrupt());

	while (test_and_set_bit(__IXGBEVF_RESETTING, &adapter->state))
		msleep(1);

	ixgbevf_down(adapter);
	ixgbevf_up(adapter);

	clear_bit(__IXGBEVF_RESETTING, &adapter->state);
}