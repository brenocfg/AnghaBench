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
typedef  int u32 ;
struct sa11x0_dma_phy {scalar_t__ base; int /*<<< orphan*/  dcsr; int /*<<< orphan*/ * dbt; int /*<<< orphan*/ * dbs; struct sa11x0_dma_desc* txd_load; struct sa11x0_dma_desc* txd_done; } ;
struct sa11x0_dma_dev {struct sa11x0_dma_phy* phy; } ;
struct sa11x0_dma_desc {int /*<<< orphan*/  ddar; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DCSR_BIU ; 
 int DCSR_RUN ; 
 int DCSR_STRTA ; 
 int DCSR_STRTB ; 
 scalar_t__ DMA_DBSA ; 
 scalar_t__ DMA_DBSB ; 
 scalar_t__ DMA_DBTA ; 
 scalar_t__ DMA_DBTB ; 
 scalar_t__ DMA_DCSR_R ; 
 scalar_t__ DMA_DCSR_S ; 
 scalar_t__ DMA_DDAR ; 
 unsigned int NR_PHY_CHAN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sa11x0_dma_dev* dev_get_drvdata (struct device*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sa11x0_dma_resume(struct device *dev)
{
	struct sa11x0_dma_dev *d = dev_get_drvdata(dev);
	unsigned pch;

	for (pch = 0; pch < NR_PHY_CHAN; pch++) {
		struct sa11x0_dma_phy *p = &d->phy[pch];
		struct sa11x0_dma_desc *txd = NULL;
		u32 dcsr = readl_relaxed(p->base + DMA_DCSR_R);

		WARN_ON(dcsr & (DCSR_BIU | DCSR_STRTA | DCSR_STRTB | DCSR_RUN));

		if (p->txd_done)
			txd = p->txd_done;
		else if (p->txd_load)
			txd = p->txd_load;

		if (!txd)
			continue;

		writel_relaxed(txd->ddar, p->base + DMA_DDAR);

		writel_relaxed(p->dbs[0], p->base + DMA_DBSA);
		writel_relaxed(p->dbt[0], p->base + DMA_DBTA);
		writel_relaxed(p->dbs[1], p->base + DMA_DBSB);
		writel_relaxed(p->dbt[1], p->base + DMA_DBTB);
		writel_relaxed(p->dcsr, p->base + DMA_DCSR_S);
	}

	return 0;
}