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
struct igb_adapter {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IGB_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_down (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_up (struct igb_adapter*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void igb_reinit_locked(struct igb_adapter *adapter)
{
	WARN_ON(in_interrupt());
	while (test_and_set_bit(__IGB_RESETTING, &adapter->state))
		usleep_range(1000, 2000);
	igb_down(adapter);
	igb_up(adapter);
	clear_bit(__IGB_RESETTING, &adapter->state);
}