#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* rebind_hw_stats ) (struct fm10k_hw*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mac; } ;
struct fm10k_intfc {int host_ready; int /*<<< orphan*/  state; scalar_t__ link_down_event; int /*<<< orphan*/  stats; TYPE_3__* pdev; struct fm10k_hw hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  __FM10K_LINK_DOWN ; 
 int /*<<< orphan*/  __FM10K_RESET_SUSPENDED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int fm10k_handle_reset (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_macvlan_schedule (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_start_service_event (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_watchdog_host_not_ready (struct fm10k_intfc*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fm10k_handle_resume(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;
	int err;

	/* Even if we didn't properly prepare for reset in
	 * fm10k_prepare_suspend, we'll attempt to resume anyways.
	 */
	if (!test_and_clear_bit(__FM10K_RESET_SUSPENDED, interface->state))
		dev_warn(&interface->pdev->dev,
			 "Device was shut down as part of suspend... Attempting to recover\n");

	/* reset statistics starting values */
	hw->mac.ops.rebind_hw_stats(hw, &interface->stats);

	err = fm10k_handle_reset(interface);
	if (err)
		return err;

	/* assume host is not ready, to prevent race with watchdog in case we
	 * actually don't have connection to the switch
	 */
	interface->host_ready = false;
	fm10k_watchdog_host_not_ready(interface);

	/* force link to stay down for a second to prevent link flutter */
	interface->link_down_event = jiffies + (HZ);
	set_bit(__FM10K_LINK_DOWN, interface->state);

	/* restart the service task */
	fm10k_start_service_event(interface);

	/* Restart the MAC/VLAN request queue in-case of outstanding events */
	fm10k_macvlan_schedule(interface);

	return 0;
}