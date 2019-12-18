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
struct e1000_adapter {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __E1000_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000e_down (struct e1000_adapter*,int) ; 
 int /*<<< orphan*/  e1000e_up (struct e1000_adapter*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void e1000e_reinit_locked(struct e1000_adapter *adapter)
{
	might_sleep();
	while (test_and_set_bit(__E1000_RESETTING, &adapter->state))
		usleep_range(1000, 1100);
	e1000e_down(adapter, true);
	e1000e_up(adapter);
	clear_bit(__E1000_RESETTING, &adapter->state);
}