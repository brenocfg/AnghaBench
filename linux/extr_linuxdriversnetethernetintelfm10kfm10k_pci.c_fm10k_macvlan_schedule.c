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
struct fm10k_intfc {int /*<<< orphan*/  state; int /*<<< orphan*/  macvlan_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  __FM10K_MACVLAN_DISABLE ; 
 int /*<<< orphan*/  __FM10K_MACVLAN_REQUEST ; 
 int /*<<< orphan*/  __FM10K_MACVLAN_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_workqueue ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fm10k_macvlan_schedule(struct fm10k_intfc *interface)
{
	/* Avoid processing the MAC/VLAN queue when the service task is
	 * disabled, or when we're resetting the device.
	 */
	if (!test_bit(__FM10K_MACVLAN_DISABLE, interface->state) &&
	    !test_and_set_bit(__FM10K_MACVLAN_SCHED, interface->state)) {
		clear_bit(__FM10K_MACVLAN_REQUEST, interface->state);
		/* We delay the actual start of execution in order to allow
		 * multiple MAC/VLAN updates to accumulate before handling
		 * them, and to allow some time to let the mailbox drain
		 * between runs.
		 */
		queue_delayed_work(fm10k_workqueue,
				   &interface->macvlan_task, 10);
	} else {
		set_bit(__FM10K_MACVLAN_REQUEST, interface->state);
	}
}