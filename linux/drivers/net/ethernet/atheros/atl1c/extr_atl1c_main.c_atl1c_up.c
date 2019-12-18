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
struct atl1c_adapter {int /*<<< orphan*/  napi; int /*<<< orphan*/  flags; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __AT_DOWN ; 
 int /*<<< orphan*/  atl1c_check_link_status (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_clean_rx_ring (struct atl1c_adapter*) ; 
 int atl1c_configure (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_irq_enable (struct atl1c_adapter*) ; 
 int atl1c_request_irq (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atl1c_up(struct atl1c_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int err;

	netif_carrier_off(netdev);

	err = atl1c_configure(adapter);
	if (unlikely(err))
		goto err_up;

	err = atl1c_request_irq(adapter);
	if (unlikely(err))
		goto err_up;

	atl1c_check_link_status(adapter);
	clear_bit(__AT_DOWN, &adapter->flags);
	napi_enable(&adapter->napi);
	atl1c_irq_enable(adapter);
	netif_start_queue(netdev);
	return err;

err_up:
	atl1c_clean_rx_ring(adapter);
	return err;
}