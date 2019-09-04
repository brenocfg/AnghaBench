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
struct ql_adapter {int rx_ring_count; int tx_ring_count; int /*<<< orphan*/  ndev; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * rx_ring; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ql_alloc_rx_resources (struct ql_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ ql_alloc_shadow_space (struct ql_adapter*) ; 
 scalar_t__ ql_alloc_tx_resources (struct ql_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_free_mem_resources (struct ql_adapter*) ; 

__attribute__((used)) static int ql_alloc_mem_resources(struct ql_adapter *qdev)
{
	int i;

	/* Allocate space for our shadow registers and such. */
	if (ql_alloc_shadow_space(qdev))
		return -ENOMEM;

	for (i = 0; i < qdev->rx_ring_count; i++) {
		if (ql_alloc_rx_resources(qdev, &qdev->rx_ring[i]) != 0) {
			netif_err(qdev, ifup, qdev->ndev,
				  "RX resource allocation failed.\n");
			goto err_mem;
		}
	}
	/* Allocate tx queue resources */
	for (i = 0; i < qdev->tx_ring_count; i++) {
		if (ql_alloc_tx_resources(qdev, &qdev->tx_ring[i]) != 0) {
			netif_err(qdev, ifup, qdev->ndev,
				  "TX resource allocation failed.\n");
			goto err_mem;
		}
	}
	return 0;

err_mem:
	ql_free_mem_resources(qdev);
	return -ENOMEM;
}