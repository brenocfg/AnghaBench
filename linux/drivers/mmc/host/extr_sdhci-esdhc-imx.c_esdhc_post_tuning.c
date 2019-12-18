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
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ ESDHC_MIX_CTRL ; 
 int /*<<< orphan*/  ESDHC_MIX_CTRL_AUTO_TUNE_EN ; 
 int /*<<< orphan*/  ESDHC_MIX_CTRL_EXE_TUNE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void esdhc_post_tuning(struct sdhci_host *host)
{
	u32 reg;

	reg = readl(host->ioaddr + ESDHC_MIX_CTRL);
	reg &= ~ESDHC_MIX_CTRL_EXE_TUNE;
	reg |= ESDHC_MIX_CTRL_AUTO_TUNE_EN;
	writel(reg, host->ioaddr + ESDHC_MIX_CTRL);
}