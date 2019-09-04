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
struct net_device {int dummy; } ;
struct fm10k_intfc {scalar_t__ last_reset; int /*<<< orphan*/  pdev; int /*<<< orphan*/  state; struct net_device* netdev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __FM10K_RESETTING ; 
 int /*<<< orphan*/  fm10k_clear_queueing_scheme (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_close (struct net_device*) ; 
 int /*<<< orphan*/  fm10k_iov_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_mbx_free_irq (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_stop_macvlan_task (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ jiffies ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fm10k_prepare_for_reset(struct fm10k_intfc *interface)
{
	struct net_device *netdev = interface->netdev;

	WARN_ON(in_interrupt());

	/* put off any impending NetWatchDogTimeout */
	netif_trans_update(netdev);

	/* Nothing to do if a reset is already in progress */
	if (test_and_set_bit(__FM10K_RESETTING, interface->state))
		return false;

	/* As the MAC/VLAN task will be accessing registers it must not be
	 * running while we reset. Although the task will not be scheduled
	 * once we start resetting it may already be running
	 */
	fm10k_stop_macvlan_task(interface);

	rtnl_lock();

	fm10k_iov_suspend(interface->pdev);

	if (netif_running(netdev))
		fm10k_close(netdev);

	fm10k_mbx_free_irq(interface);

	/* free interrupts */
	fm10k_clear_queueing_scheme(interface);

	/* delay any future reset requests */
	interface->last_reset = jiffies + (10 * HZ);

	rtnl_unlock();

	return true;
}