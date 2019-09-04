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
struct ixgbevf_adapter {int /*<<< orphan*/  state; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  __IXGBEVF_QUEUE_RESET_REQUESTED ; 
 int /*<<< orphan*/  __IXGBEVF_RESETTING ; 
 int /*<<< orphan*/  ixgbevf_clear_interrupt_scheme (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_close (struct net_device*) ; 
 int /*<<< orphan*/  ixgbevf_init_interrupt_scheme (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_open (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbevf_queue_reset_subtask(struct ixgbevf_adapter *adapter)
{
	struct net_device *dev = adapter->netdev;

	if (!test_and_clear_bit(__IXGBEVF_QUEUE_RESET_REQUESTED,
				&adapter->state))
		return;

	/* if interface is down do nothing */
	if (test_bit(__IXGBEVF_DOWN, &adapter->state) ||
	    test_bit(__IXGBEVF_RESETTING, &adapter->state))
		return;

	/* Hardware has to reinitialize queues and interrupts to
	 * match packet buffer alignment. Unfortunately, the
	 * hardware is not flexible enough to do this dynamically.
	 */
	rtnl_lock();

	if (netif_running(dev))
		ixgbevf_close(dev);

	ixgbevf_clear_interrupt_scheme(adapter);
	ixgbevf_init_interrupt_scheme(adapter);

	if (netif_running(dev))
		ixgbevf_open(dev);

	rtnl_unlock();
}