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
struct tx_port_stats_ext {int dummy; } ;
struct rx_port_stats_ext {int dummy; } ;
struct pcie_ctx_hw_stats {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt {int hw_port_stats_size; int /*<<< orphan*/ * hw_pcie_stats; int /*<<< orphan*/  hw_pcie_stats_map; int /*<<< orphan*/ * hw_rx_port_stats_ext; int /*<<< orphan*/  hw_rx_port_stats_ext_map; int /*<<< orphan*/ * hw_tx_port_stats_ext; int /*<<< orphan*/  hw_tx_port_stats_ext_map; int /*<<< orphan*/ * hw_rx_port_stats; int /*<<< orphan*/  hw_rx_port_stats_map; int /*<<< orphan*/  flags; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FLAG_PORT_STATS ; 
 int /*<<< orphan*/  BNXT_FLAG_PORT_STATS_EXT ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_free_port_stats(struct bnxt *bp)
{
	struct pci_dev *pdev = bp->pdev;

	bp->flags &= ~BNXT_FLAG_PORT_STATS;
	bp->flags &= ~BNXT_FLAG_PORT_STATS_EXT;

	if (bp->hw_rx_port_stats) {
		dma_free_coherent(&pdev->dev, bp->hw_port_stats_size,
				  bp->hw_rx_port_stats,
				  bp->hw_rx_port_stats_map);
		bp->hw_rx_port_stats = NULL;
	}

	if (bp->hw_tx_port_stats_ext) {
		dma_free_coherent(&pdev->dev, sizeof(struct tx_port_stats_ext),
				  bp->hw_tx_port_stats_ext,
				  bp->hw_tx_port_stats_ext_map);
		bp->hw_tx_port_stats_ext = NULL;
	}

	if (bp->hw_rx_port_stats_ext) {
		dma_free_coherent(&pdev->dev, sizeof(struct rx_port_stats_ext),
				  bp->hw_rx_port_stats_ext,
				  bp->hw_rx_port_stats_ext_map);
		bp->hw_rx_port_stats_ext = NULL;
	}

	if (bp->hw_pcie_stats) {
		dma_free_coherent(&pdev->dev, sizeof(struct pcie_ctx_hw_stats),
				  bp->hw_pcie_stats, bp->hw_pcie_stats_map);
		bp->hw_pcie_stats = NULL;
	}
}