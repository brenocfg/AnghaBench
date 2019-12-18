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
struct ql_adapter {int /*<<< orphan*/  rx_ring_shadow_reg_dma; int /*<<< orphan*/ * rx_ring_shadow_reg_area; int /*<<< orphan*/  pdev; int /*<<< orphan*/  ndev; int /*<<< orphan*/ * tx_ring_shadow_reg_area; int /*<<< orphan*/  tx_ring_shadow_reg_dma; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* pci_zalloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_alloc_shadow_space(struct ql_adapter *qdev)
{
	qdev->rx_ring_shadow_reg_area =
		pci_zalloc_consistent(qdev->pdev, PAGE_SIZE,
				      &qdev->rx_ring_shadow_reg_dma);
	if (qdev->rx_ring_shadow_reg_area == NULL) {
		netif_err(qdev, ifup, qdev->ndev,
			  "Allocation of RX shadow space failed.\n");
		return -ENOMEM;
	}

	qdev->tx_ring_shadow_reg_area =
		pci_zalloc_consistent(qdev->pdev, PAGE_SIZE,
				      &qdev->tx_ring_shadow_reg_dma);
	if (qdev->tx_ring_shadow_reg_area == NULL) {
		netif_err(qdev, ifup, qdev->ndev,
			  "Allocation of TX shadow space failed.\n");
		goto err_wqp_sh_area;
	}
	return 0;

err_wqp_sh_area:
	pci_free_consistent(qdev->pdev,
			    PAGE_SIZE,
			    qdev->rx_ring_shadow_reg_area,
			    qdev->rx_ring_shadow_reg_dma);
	return -ENOMEM;
}