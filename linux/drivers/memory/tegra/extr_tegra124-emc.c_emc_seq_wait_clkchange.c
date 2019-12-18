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
 scalar_t__ EMC_INTSTATUS ; 
 int EMC_INTSTATUS_CLKCHANGE_COMPLETE ; 
 unsigned int EMC_STATUS_UPDATE_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void emc_seq_wait_clkchange(struct tegra_emc *emc)
{
	unsigned int i;
	u32 value;

	for (i = 0; i < EMC_STATUS_UPDATE_TIMEOUT; ++i) {
		value = readl(emc->regs + EMC_INTSTATUS);
		if (value & EMC_INTSTATUS_CLKCHANGE_COMPLETE)
			return;
		udelay(1);
	}

	dev_err(emc->dev, "clock change timed out\n");
}