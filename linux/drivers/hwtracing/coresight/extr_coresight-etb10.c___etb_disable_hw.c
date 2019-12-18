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
struct etb_drvdata {scalar_t__ base; TYPE_1__* csdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ ETB_CTL_REG ; 
 scalar_t__ ETB_FFCR ; 
 int /*<<< orphan*/  ETB_FFCR_BIT ; 
 int ETB_FFCR_FON_MAN ; 
 int ETB_FFCR_STOP_FI ; 
 scalar_t__ ETB_FFSR ; 
 int /*<<< orphan*/  ETB_FFSR_BIT ; 
 scalar_t__ coresight_timeout (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void __etb_disable_hw(struct etb_drvdata *drvdata)
{
	u32 ffcr;
	struct device *dev = &drvdata->csdev->dev;

	CS_UNLOCK(drvdata->base);

	ffcr = readl_relaxed(drvdata->base + ETB_FFCR);
	/* stop formatter when a stop has completed */
	ffcr |= ETB_FFCR_STOP_FI;
	writel_relaxed(ffcr, drvdata->base + ETB_FFCR);
	/* manually generate a flush of the system */
	ffcr |= ETB_FFCR_FON_MAN;
	writel_relaxed(ffcr, drvdata->base + ETB_FFCR);

	if (coresight_timeout(drvdata->base, ETB_FFCR, ETB_FFCR_BIT, 0)) {
		dev_err(dev,
		"timeout while waiting for completion of Manual Flush\n");
	}

	/* disable trace capture */
	writel_relaxed(0x0, drvdata->base + ETB_CTL_REG);

	if (coresight_timeout(drvdata->base, ETB_FFSR, ETB_FFSR_BIT, 1)) {
		dev_err(dev,
			"timeout while waiting for Formatter to Stop\n");
	}

	CS_LOCK(drvdata->base);
}