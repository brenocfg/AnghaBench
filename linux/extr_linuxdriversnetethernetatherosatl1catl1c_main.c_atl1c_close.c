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
struct atl1c_adapter {int /*<<< orphan*/  common_task; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __AT_DOWN ; 
 int /*<<< orphan*/  __AT_RESETTING ; 
 int /*<<< orphan*/  atl1c_down (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_free_ring_resources (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl1c_close(struct net_device *netdev)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);

	WARN_ON(test_bit(__AT_RESETTING, &adapter->flags));
	set_bit(__AT_DOWN, &adapter->flags);
	cancel_work_sync(&adapter->common_task);
	atl1c_down(adapter);
	atl1c_free_ring_resources(adapter);
	return 0;
}