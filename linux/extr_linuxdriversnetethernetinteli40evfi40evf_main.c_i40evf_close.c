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
struct i40evf_adapter {scalar_t__ state; int /*<<< orphan*/  down_waitqueue; int /*<<< orphan*/  crit_section; int /*<<< orphan*/  flags; TYPE_1__ vsi; } ;

/* Variables and functions */
 scalar_t__ CLIENT_ENABLED (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  I40EVF_FLAG_CLIENT_NEEDS_CLOSE ; 
 scalar_t__ __I40EVF_DOWN ; 
 scalar_t__ __I40EVF_DOWN_PENDING ; 
 int /*<<< orphan*/  __I40EVF_IN_CRITICAL_TASK ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40evf_down (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_free_traffic_irqs (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct i40evf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40evf_close(struct net_device *netdev)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);
	int status;

	if (adapter->state <= __I40EVF_DOWN_PENDING)
		return 0;

	while (test_and_set_bit(__I40EVF_IN_CRITICAL_TASK,
				&adapter->crit_section))
		usleep_range(500, 1000);

	set_bit(__I40E_VSI_DOWN, adapter->vsi.state);
	if (CLIENT_ENABLED(adapter))
		adapter->flags |= I40EVF_FLAG_CLIENT_NEEDS_CLOSE;

	i40evf_down(adapter);
	adapter->state = __I40EVF_DOWN_PENDING;
	i40evf_free_traffic_irqs(adapter);

	clear_bit(__I40EVF_IN_CRITICAL_TASK, &adapter->crit_section);

	/* We explicitly don't free resources here because the hardware is
	 * still active and can DMA into memory. Resources are cleared in
	 * i40evf_virtchnl_completion() after we get confirmation from the PF
	 * driver that the rings have been stopped.
	 *
	 * Also, we wait for state to transition to __I40EVF_DOWN before
	 * returning. State change occurs in i40evf_virtchnl_completion() after
	 * VF resources are released (which occurs after PF driver processes and
	 * responds to admin queue commands).
	 */

	status = wait_event_timeout(adapter->down_waitqueue,
				    adapter->state == __I40EVF_DOWN,
				    msecs_to_jiffies(200));
	if (!status)
		netdev_warn(netdev, "Device resources not yet released\n");
	return 0;
}