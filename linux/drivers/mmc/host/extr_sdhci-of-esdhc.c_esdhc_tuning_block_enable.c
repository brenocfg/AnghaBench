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
 int /*<<< orphan*/  ESDHC_DMA_SYSCTL ; 
 int /*<<< orphan*/  ESDHC_FLUSH_ASYNC_FIFO ; 
 int /*<<< orphan*/  ESDHC_TBCTL ; 
 int /*<<< orphan*/  ESDHC_TB_EN ; 
 int /*<<< orphan*/  esdhc_clock_enable (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esdhc_tuning_block_enable(struct sdhci_host *host, bool enable)
{
	u32 val;

	esdhc_clock_enable(host, false);

	val = sdhci_readl(host, ESDHC_DMA_SYSCTL);
	val |= ESDHC_FLUSH_ASYNC_FIFO;
	sdhci_writel(host, val, ESDHC_DMA_SYSCTL);

	val = sdhci_readl(host, ESDHC_TBCTL);
	if (enable)
		val |= ESDHC_TB_EN;
	else
		val &= ~ESDHC_TB_EN;
	sdhci_writel(host, val, ESDHC_TBCTL);

	esdhc_clock_enable(host, true);
}