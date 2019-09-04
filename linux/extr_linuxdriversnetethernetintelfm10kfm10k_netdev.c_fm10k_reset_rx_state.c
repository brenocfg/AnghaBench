#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_lport_state ) (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mac; } ;
struct fm10k_intfc {int /*<<< orphan*/  xcast_mode; int /*<<< orphan*/  glort_count; int /*<<< orphan*/  glort; int /*<<< orphan*/  state; struct fm10k_hw hw; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_XCAST_MODE_NONE ; 
 int /*<<< orphan*/  __FM10K_MACVLAN_SCHED ; 
 int /*<<< orphan*/  __dev_mc_unsync (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dev_uc_unsync (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fm10k_clear_macvlan_queue (struct fm10k_intfc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fm10k_host_mbx_ready (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_lock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_unlock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void fm10k_reset_rx_state(struct fm10k_intfc *interface)
{
	struct net_device *netdev = interface->netdev;
	struct fm10k_hw *hw = &interface->hw;

	/* Wait for MAC/VLAN work to finish */
	while (test_bit(__FM10K_MACVLAN_SCHED, interface->state))
		usleep_range(1000, 2000);

	/* Cancel pending MAC/VLAN requests */
	fm10k_clear_macvlan_queue(interface, interface->glort, true);

	fm10k_mbx_lock(interface);

	/* clear the logical port state on lower device if host's mailbox is
	 * ready
	 */
	if (fm10k_host_mbx_ready(interface))
		hw->mac.ops.update_lport_state(hw, interface->glort,
					       interface->glort_count, false);

	fm10k_mbx_unlock(interface);

	/* reset flags to default state */
	interface->xcast_mode = FM10K_XCAST_MODE_NONE;

	/* clear the sync flag since the lport has been dropped */
	__dev_uc_unsync(netdev, NULL);
	__dev_mc_unsync(netdev, NULL);
}