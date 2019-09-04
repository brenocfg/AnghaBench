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
struct tegra_emc {int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ EMC_STATUS ; 
 int EMC_STATUS_TIMING_UPDATE_STALLED ; 
 unsigned int EMC_STATUS_UPDATE_TIMEOUT ; 
 scalar_t__ EMC_TIMING_CONTROL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void emc_seq_update_timing(struct tegra_emc *emc)
{
	unsigned int i;
	u32 value;

	writel(1, emc->regs + EMC_TIMING_CONTROL);

	for (i = 0; i < EMC_STATUS_UPDATE_TIMEOUT; ++i) {
		value = readl(emc->regs + EMC_STATUS);
		if ((value & EMC_STATUS_TIMING_UPDATE_STALLED) == 0)
			return;
		udelay(1);
	}

	dev_err(emc->dev, "timing update timed out\n");
}