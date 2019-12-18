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
struct etmv4_drvdata {int /*<<< orphan*/  cpu; TYPE_1__* csdev; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ TRCPDCR ; 
 int TRCPDCR_PU ; 
 scalar_t__ TRCPRGCTLR ; 
 int /*<<< orphan*/  coresight_disclaim_device_unlocked (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isb () ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  sy ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void etm4_disable_hw(void *info)
{
	u32 control;
	struct etmv4_drvdata *drvdata = info;

	CS_UNLOCK(drvdata->base);

	/* power can be removed from the trace unit now */
	control = readl_relaxed(drvdata->base + TRCPDCR);
	control &= ~TRCPDCR_PU;
	writel_relaxed(control, drvdata->base + TRCPDCR);

	control = readl_relaxed(drvdata->base + TRCPRGCTLR);

	/* EN, bit[0] Trace unit enable bit */
	control &= ~0x1;

	/*
	 * Make sure everything completes before disabling, as recommended
	 * by section 7.3.77 ("TRCVICTLR, ViewInst Main Control Register,
	 * SSTATUS") of ARM IHI 0064D
	 */
	dsb(sy);
	isb();
	writel_relaxed(control, drvdata->base + TRCPRGCTLR);

	coresight_disclaim_device_unlocked(drvdata->base);

	CS_LOCK(drvdata->base);

	dev_dbg(&drvdata->csdev->dev,
		"cpu: %d disable smp call done\n", drvdata->cpu);
}