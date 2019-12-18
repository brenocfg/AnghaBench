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
struct igbvf_adapter {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IGBVF_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igbvf_down (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_up (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void igbvf_reinit_locked(struct igbvf_adapter *adapter)
{
	might_sleep();
	while (test_and_set_bit(__IGBVF_RESETTING, &adapter->state))
		usleep_range(1000, 2000);
	igbvf_down(adapter);
	igbvf_up(adapter);
	clear_bit(__IGBVF_RESETTING, &adapter->state);
}