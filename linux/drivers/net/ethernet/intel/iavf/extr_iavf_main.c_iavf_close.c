#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct iavf_adapter {scalar_t__ state; int /*<<< orphan*/  down_waitqueue; int /*<<< orphan*/  crit_section; int /*<<< orphan*/  flags; TYPE_1__ vsi; } ;

/* Variables and functions */
 scalar_t__ CLIENT_ENABLED (struct iavf_adapter*) ; 
 int /*<<< orphan*/  IAVF_FLAG_CLIENT_NEEDS_CLOSE ; 
 scalar_t__ __IAVF_DOWN ; 
 scalar_t__ __IAVF_DOWN_PENDING ; 
 int /*<<< orphan*/  __IAVF_IN_CRITICAL_TASK ; 
 int /*<<< orphan*/  __IAVF_VSI_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iavf_down (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_free_traffic_irqs (struct iavf_adapter*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iavf_close(struct net_device *netdev)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);
	int status;

	if (adapter->state <= __IAVF_DOWN_PENDING)
		return 0;

	while (test_and_set_bit(__IAVF_IN_CRITICAL_TASK,
				&adapter->crit_section))
		usleep_range(500, 1000);

	set_bit(__IAVF_VSI_DOWN, adapter->vsi.state);
	if (CLIENT_ENABLED(adapter))
		adapter->flags |= IAVF_FLAG_CLIENT_NEEDS_CLOSE;

	iavf_down(adapter);
	adapter->state = __IAVF_DOWN_PENDING;
	iavf_free_traffic_irqs(adapter);

	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);

	/* We explicitly don't free resources here because the hardware is
	 * still active and can DMA into memory. Resources are cleared in
	 * iavf_virtchnl_completion() after we get confirmation from the PF
	 * driver that the rings have been stopped.
	 *
	 * Also, we wait for state to transition to __IAVF_DOWN before
	 * returning. State change occurs in iavf_virtchnl_completion() after
	 * VF resources are released (which occurs after PF driver processes and
	 * responds to admin queue commands).
	 */

	status = wait_event_timeout(adapter->down_waitqueue,
				    adapter->state == __IAVF_DOWN,
				    msecs_to_jiffies(500));
	if (!status)
		netdev_warn(netdev, "Device resources not yet released\n");
	return 0;
}