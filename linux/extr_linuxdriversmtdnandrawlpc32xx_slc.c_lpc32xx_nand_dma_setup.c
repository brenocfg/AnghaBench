#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct mtd_info {TYPE_2__ dev; } ;
struct lpc32xx_nand_host {int /*<<< orphan*/  dma_chan; TYPE_1__* pdata; int /*<<< orphan*/  nand_chip; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_3__ {int /*<<< orphan*/  dma_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc32xx_nand_dma_setup(struct lpc32xx_nand_host *host)
{
	struct mtd_info *mtd = nand_to_mtd(&host->nand_chip);
	dma_cap_mask_t mask;

	if (!host->pdata || !host->pdata->dma_filter) {
		dev_err(mtd->dev.parent, "no DMA platform data\n");
		return -ENOENT;
	}

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	host->dma_chan = dma_request_channel(mask, host->pdata->dma_filter,
					     "nand-slc");
	if (!host->dma_chan) {
		dev_err(mtd->dev.parent, "Failed to request DMA channel\n");
		return -EBUSY;
	}

	return 0;
}