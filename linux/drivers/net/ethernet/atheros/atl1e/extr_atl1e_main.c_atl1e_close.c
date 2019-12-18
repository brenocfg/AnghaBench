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
struct atl1e_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __AT_RESETTING ; 
 int /*<<< orphan*/  atl1e_down (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_free_irq (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_free_ring_resources (struct atl1e_adapter*) ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl1e_close(struct net_device *netdev)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);

	WARN_ON(test_bit(__AT_RESETTING, &adapter->flags));
	atl1e_down(adapter);
	atl1e_free_irq(adapter);
	atl1e_free_ring_resources(adapter);

	return 0;
}