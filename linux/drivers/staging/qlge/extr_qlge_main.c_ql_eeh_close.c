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
struct ql_adapter {int rss_ring_count; int /*<<< orphan*/  flags; TYPE_1__* rx_ring; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ADAPTER_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  ql_cancel_all_work_sync (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_free_rx_buffers (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_release_adapter_resources (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_tx_ring_clean (struct ql_adapter*) ; 

__attribute__((used)) static void ql_eeh_close(struct net_device *ndev)
{
	int i;
	struct ql_adapter *qdev = netdev_priv(ndev);

	if (netif_carrier_ok(ndev)) {
		netif_carrier_off(ndev);
		netif_stop_queue(ndev);
	}

	/* Disabling the timer */
	ql_cancel_all_work_sync(qdev);

	for (i = 0; i < qdev->rss_ring_count; i++)
		netif_napi_del(&qdev->rx_ring[i].napi);

	clear_bit(QL_ADAPTER_UP, &qdev->flags);
	ql_tx_ring_clean(qdev);
	ql_free_rx_buffers(qdev);
	ql_release_adapter_resources(qdev);
}