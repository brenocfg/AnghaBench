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
typedef  int u32 ;
struct macb_config {int /*<<< orphan*/  caps; } ;
struct macb {int /*<<< orphan*/  caps; TYPE_1__* pdev; int /*<<< orphan*/ * ptp_info; int /*<<< orphan*/  hw_dma_cap; int /*<<< orphan*/  native_io; int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCFG1 ; 
 int /*<<< orphan*/  DCFG2 ; 
 int /*<<< orphan*/  DCFG5 ; 
 scalar_t__ GEM_BFEXT (int /*<<< orphan*/ ,int) ; 
 int GEM_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HW_DMA_CAP_PTP ; 
 int /*<<< orphan*/  IRQCOR ; 
 int /*<<< orphan*/  MACB_CAPS_FIFO_MODE ; 
 int /*<<< orphan*/  MACB_CAPS_ISR_CLEAR_ON_WRITE ; 
 int /*<<< orphan*/  MACB_CAPS_MACB_IS_GEM ; 
 int /*<<< orphan*/  RX_PKT_BUFF ; 
 int /*<<< orphan*/  TSU ; 
 int /*<<< orphan*/  TX_PKT_BUFF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ gem_has_ptp (struct macb*) ; 
 int /*<<< orphan*/  gem_ptp_info ; 
 int gem_readl (struct macb*,int /*<<< orphan*/ ) ; 
 scalar_t__ hw_is_gem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void macb_configure_caps(struct macb *bp,
				const struct macb_config *dt_conf)
{
	u32 dcfg;

	if (dt_conf)
		bp->caps = dt_conf->caps;

	if (hw_is_gem(bp->regs, bp->native_io)) {
		bp->caps |= MACB_CAPS_MACB_IS_GEM;

		dcfg = gem_readl(bp, DCFG1);
		if (GEM_BFEXT(IRQCOR, dcfg) == 0)
			bp->caps |= MACB_CAPS_ISR_CLEAR_ON_WRITE;
		dcfg = gem_readl(bp, DCFG2);
		if ((dcfg & (GEM_BIT(RX_PKT_BUFF) | GEM_BIT(TX_PKT_BUFF))) == 0)
			bp->caps |= MACB_CAPS_FIFO_MODE;
#ifdef CONFIG_MACB_USE_HWSTAMP
		if (gem_has_ptp(bp)) {
			if (!GEM_BFEXT(TSU, gem_readl(bp, DCFG5)))
				pr_err("GEM doesn't support hardware ptp.\n");
			else {
				bp->hw_dma_cap |= HW_DMA_CAP_PTP;
				bp->ptp_info = &gem_ptp_info;
			}
		}
#endif
	}

	dev_dbg(&bp->pdev->dev, "Cadence caps 0x%08x\n", bp->caps);
}