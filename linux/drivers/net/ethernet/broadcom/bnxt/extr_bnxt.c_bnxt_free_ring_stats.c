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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt_cp_ring_info {int /*<<< orphan*/ * hw_stats; int /*<<< orphan*/  hw_stats_map; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int hw_ring_stats_size; int cp_nr_rings; struct bnxt_napi** bnapi; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_free_ring_stats(struct bnxt *bp)
{
	struct pci_dev *pdev = bp->pdev;
	int size, i;

	if (!bp->bnapi)
		return;

	size = bp->hw_ring_stats_size;

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