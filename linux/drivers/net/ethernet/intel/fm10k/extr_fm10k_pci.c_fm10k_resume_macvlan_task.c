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
struct fm10k_intfc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __FM10K_MACVLAN_DISABLE ; 
 int /*<<< orphan*/  __FM10K_MACVLAN_REQUEST ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_macvlan_schedule (struct fm10k_intfc*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_resume_macvlan_task(struct fm10k_intfc *interface)
{
	/* Re-enable the MAC/VLAN work item */
	clear_bit(__FM10K_MACVLAN_DISABLE, interface->state);

	/* We might have received a MAC/VLAN request while disabled. If so,
	 * kick off the queue now.
	 */
	if (test_bit(__FM10K_MACVLAN_REQUEST, interface->state))
		fm10k_macvlan_schedule(interface);
}