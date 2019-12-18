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
struct tmc_drvdata {int trigger_cntr; scalar_t__ base; struct etr_buf* etr_buf; } ;
struct etr_buf {int size; scalar_t__ mode; int /*<<< orphan*/  hwaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ ETR_MODE_ETR_SG ; 
 scalar_t__ TMC_AXICTL ; 
 int TMC_AXICTL_ARCACHE_MASK ; 
 int TMC_AXICTL_ARCACHE_OS ; 
 int TMC_AXICTL_AXCACHE_OS ; 
 int TMC_AXICTL_CLEAR_MASK ; 
 int TMC_AXICTL_PROT_CTL_B1 ; 
 int TMC_AXICTL_SCT_GAT_MODE ; 
 int TMC_AXICTL_WR_BURST_16 ; 
 int /*<<< orphan*/  TMC_ETR_AXI_ARCACHE ; 
 int /*<<< orphan*/  TMC_ETR_SAVE_RESTORE ; 
 scalar_t__ TMC_FFCR ; 
 int TMC_FFCR_EN_FMT ; 
 int TMC_FFCR_EN_TI ; 
 int TMC_FFCR_FON_FLIN ; 
 int TMC_FFCR_FON_TRIG_EVT ; 
 int TMC_FFCR_TRIGON_TRIGIN ; 
 scalar_t__ TMC_MODE ; 
 int TMC_MODE_CIRCULAR_BUFFER ; 
 scalar_t__ TMC_RSZ ; 
 scalar_t__ TMC_STS ; 
 int TMC_STS_FULL ; 
 scalar_t__ TMC_TRG ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  tmc_enable_hw (struct tmc_drvdata*) ; 
 scalar_t__ tmc_etr_has_cap (struct tmc_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_wait_for_tmcready (struct tmc_drvdata*) ; 
 int /*<<< orphan*/  tmc_write_dba (struct tmc_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_write_rrp (struct tmc_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_write_rwp (struct tmc_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void __tmc_etr_enable_hw(struct tmc_drvdata *drvdata)
{
	u32 axictl, sts;
	struct etr_buf *etr_buf = drvdata->etr_buf;

	CS_UNLOCK(drvdata->base);

	/* Wait for TMCSReady bit to be set */
	tmc_wait_for_tmcready(drvdata);

	writel_relaxed(etr_buf->size / 4, drvdata->base + TMC_RSZ);
	writel_relaxed(TMC_MODE_CIRCULAR_BUFFER, drvdata->base + TMC_MODE);

	axictl = readl_relaxed(drvdata->base + TMC_AXICTL);
	axictl &= ~TMC_AXICTL_CLEAR_MASK;
	axictl |= (TMC_AXICTL_PROT_CTL_B1 | TMC_AXICTL_WR_BURST_16);
	axictl |= TMC_AXICTL_AXCACHE_OS;

	if (tmc_etr_has_cap(drvdata, TMC_ETR_AXI_ARCACHE)) {
		axictl &= ~TMC_AXICTL_ARCACHE_MASK;
		axictl |= TMC_AXICTL_ARCACHE_OS;
	}

	if (etr_buf->mode == ETR_MODE_ETR_SG)
		axictl |= TMC_AXICTL_SCT_GAT_MODE;

	writel_relaxed(axictl, drvdata->base + TMC_AXICTL);
	tmc_write_dba(drvdata, etr_buf->hwaddr);
	/*
	 * If the TMC pointers must be programmed before the session,
	 * we have to set it properly (i.e, RRP/RWP to base address and
	 * STS to "not full").
	 */
	if (tmc_etr_has_cap(drvdata, TMC_ETR_SAVE_RESTORE)) {
		tmc_write_rrp(drvdata, etr_buf->hwaddr);
		tmc_write_rwp(drvdata, etr_buf->hwaddr);
		sts = readl_relaxed(drvdata->base + TMC_STS) & ~TMC_STS_FULL;
		writel_relaxed(sts, drvdata->base + TMC_STS);
	}

	writel_relaxed(TMC_FFCR_EN_FMT | TMC_FFCR_EN_TI |
		       TMC_FFCR_FON_FLIN | TMC_FFCR_FON_TRIG_EVT |
		       TMC_FFCR_TRIGON_TRIGIN,
		       drvdata->base + TMC_FFCR);
	writel_relaxed(drvdata->trigger_cntr, drvdata->base + TMC_TRG);
	tmc_enable_hw(drvdata);

	CS_LOCK(drvdata->base);
}