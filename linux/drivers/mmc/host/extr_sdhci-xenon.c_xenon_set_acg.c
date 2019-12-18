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
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XENON_AUTO_CLKGATE_DISABLE_MASK ; 
 int /*<<< orphan*/  XENON_SYS_OP_CTRL ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xenon_set_acg(struct sdhci_host *host, bool enable)
{
	u32 reg;

	reg = sdhci_readl(host, XENON_SYS_OP_CTRL);
	if (enable)
		reg &= ~XENON_AUTO_CLKGATE_DISABLE_MASK;
	else
		reg |= XENON_AUTO_CLKGATE_DISABLE_MASK;
	sdhci_writel(host, reg, XENON_SYS_OP_CTRL);
}