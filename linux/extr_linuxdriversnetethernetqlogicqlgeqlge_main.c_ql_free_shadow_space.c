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
struct ql_adapter {int /*<<< orphan*/ * tx_ring_shadow_reg_area; int /*<<< orphan*/  tx_ring_shadow_reg_dma; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * rx_ring_shadow_reg_area; int /*<<< orphan*/  rx_ring_shadow_reg_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql_free_shadow_space(struct ql_adapter *qdev)
{
	if (qdev->rx_ring_shadow_reg_area) {
		pci_free_consistent(qdev->pdev,
				    PAGE_SIZE,
				    qdev->rx_ring_shadow_reg_area,
				    qdev->rx_ring_shadow_reg_dma);
		qdev->rx_ring_shadow_reg_area = NULL;
	}
	if (qdev->tx_ring_shadow_reg_area) {
		pci_free_consistent(qdev->pdev,
				    PAGE_SIZE,
				    qdev->tx_ring_shadow_reg_area,
				    qdev->tx_ring_shadow_reg_dma);
		qdev->tx_ring_shadow_reg_area = NULL;
	}
}