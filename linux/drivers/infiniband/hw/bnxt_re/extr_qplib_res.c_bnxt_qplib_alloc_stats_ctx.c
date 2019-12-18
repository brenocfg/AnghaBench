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
struct ctx_hw_stats {int dummy; } ;
struct bnxt_qplib_stats {int fw_id; int /*<<< orphan*/  dma; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bnxt_qplib_stats*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bnxt_qplib_alloc_stats_ctx(struct pci_dev *pdev,
				      struct bnxt_qplib_stats *stats)
{
	memset(stats, 0, sizeof(*stats));
	stats->fw_id = -1;
	/* 128 byte aligned context memory is required only for 57500.
	 * However making this unconditional, it does not harm previous
	 * generation.
	 */
	stats->size = ALIGN(sizeof(struct ctx_hw_stats), 128);
	stats->dma = dma_alloc_coherent(&pdev->dev, stats->size,
					&stats->dma_map, GFP_KERNEL);
	if (!stats->dma) {
		dev_err(&pdev->dev, "Stats DMA allocation failed\n");
		return -ENOMEM;
	}
	return 0;
}