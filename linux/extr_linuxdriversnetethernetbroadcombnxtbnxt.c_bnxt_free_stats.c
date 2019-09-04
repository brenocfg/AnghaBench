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
typedef  size_t u32 ;
struct rx_port_stats_ext {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ctx_hw_stats {int dummy; } ;
struct bnxt_cp_ring_info {int /*<<< orphan*/ * hw_stats; int /*<<< orphan*/  hw_stats_map; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {size_t hw_port_stats_size; size_t cp_nr_rings; struct bnxt_napi** bnapi; int /*<<< orphan*/ * hw_rx_port_stats_ext; int /*<<< orphan*/  hw_rx_port_stats_ext_map; int /*<<< orphan*/ * hw_rx_port_stats; int /*<<< orphan*/  hw_rx_port_stats_map; int /*<<< orphan*/  flags; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FLAG_PORT_STATS ; 
 int /*<<< orphan*/  BNXT_FLAG_PORT_STATS_EXT ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_free_stats(struct bnxt *bp)
{
	u32 size, i;
	struct pci_dev *pdev = bp->pdev;

	bp->flags &= ~BNXT_FLAG_PORT_STATS;
	bp->flags &= ~BNXT_FLAG_PORT_STATS_EXT;

	if (bp->hw_rx_port_stats) {
		dma_free_coherent(&pdev->dev, bp->hw_port_stats_size,
				  bp->hw_rx_port_stats,
				  bp->hw_rx_port_stats_map);
		bp->hw_rx_port_stats = NULL;
	}

	if (bp->hw_rx_port_stats_ext) {
		dma_free_coherent(&pdev->dev, sizeof(struct rx_port_stats_ext),
				  bp->hw_rx_port_stats_ext,
				  bp->hw_rx_port_stats_ext_map);
		bp->hw_rx_port_stats_ext = NULL;
	}

	if (!bp->bnapi)
		return;

	size = sizeof(struct ctx_hw_stats);

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;

		if (cpr->hw_stats) {
			dma_free_coherent(&pdev->dev, size, cpr->hw_stats,
					  cpr->hw_stats_map);
			cpr->hw_stats = NULL;
		}
	}
}