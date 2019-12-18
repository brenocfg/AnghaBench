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
struct atl1c_adapter {int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __AT_TESTING ; 
 int /*<<< orphan*/  atl1c_free_irq (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_free_ring_resources (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_reset_mac (int /*<<< orphan*/ *) ; 
 int atl1c_setup_ring_resources (struct atl1c_adapter*) ; 
 int atl1c_up (struct atl1c_adapter*) ; 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atl1c_open(struct net_device *netdev)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);
	int err;

	/* disallow open during test */
	if (test_bit(__AT_TESTING, &adapter->flags))
		return -EBUSY;

	/* allocate rx/tx dma buffer & descriptors */
	err = atl1c_setup_ring_resources(adapter);
	if (unlikely(err))
		return err;

	err = atl1c_up(adapter);
	if (unlikely(err))
		goto err_up;

	return 0;

err_up:
	atl1c_free_irq(adapter);
	atl1c_free_ring_resources(adapter);
	atl1c_reset_mac(&adapter->hw);
	return err;
}