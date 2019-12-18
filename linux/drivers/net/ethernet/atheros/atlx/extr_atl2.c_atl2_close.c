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
struct atl2_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ATL2_RESETTING ; 
 int /*<<< orphan*/  atl2_down (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_free_irq (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_free_ring_resources (struct atl2_adapter*) ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl2_close(struct net_device *netdev)
{
	struct atl2_adapter *adapter = netdev_priv(netdev);

	WARN_ON(test_bit(__ATL2_RESETTING, &adapter->flags));

	atl2_down(adapter);
	atl2_free_irq(adapter);
	atl2_free_ring_resources(adapter);

	return 0;
}