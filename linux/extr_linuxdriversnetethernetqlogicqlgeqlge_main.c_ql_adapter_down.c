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
struct ql_adapter {int rss_ring_count; int /*<<< orphan*/  func; int /*<<< orphan*/  ndev; TYPE_1__* rx_ring; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ADAPTER_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int ql_adapter_reset (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_cancel_all_work_sync (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_disable_interrupts (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_free_rx_buffers (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_link_off (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_tx_ring_clean (struct ql_adapter*) ; 

__attribute__((used)) static int ql_adapter_down(struct ql_adapter *qdev)
{
	int i, status = 0;

	ql_link_off(qdev);

	ql_cancel_all_work_sync(qdev);

	for (i = 0; i < qdev->rss_ring_count; i++)
		napi_disable(&qdev->rx_ring[i].napi);

	clear_bit(QL_ADAPTER_UP, &qdev->flags);

	ql_disable_interrupts(qdev);

	ql_tx_ring_clean(qdev);

	/* Call netif_napi_del() from common point.
	 */
	for (i = 0; i < qdev->rss_ring_count; i++)
		netif_napi_del(&qdev->rx_ring[i].napi);

	status = ql_adapter_reset(qdev);
	if (status)
		netif_err(qdev, ifdown, qdev->ndev, "reset(func #%d) FAILED!\n",
			  qdev->func);
	ql_free_rx_buffers(qdev);

	return status;
}