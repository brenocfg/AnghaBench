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
 int /*<<< orphan*/  BIT (unsigned char) ; 
 int /*<<< orphan*/  XENON_SYS_EXT_OP_CTRL ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xenon_enable_sdhc_parallel_tran(struct sdhci_host *host,
					    unsigned char sdhc_id)
{
	u32 reg;

	reg = sdhci_readl(host, XENON_SYS_EXT_OP_CTRL);
	reg |= BIT(sdhc_id);
	sdhci_writel(host, reg, XENON_SYS_EXT_OP_CTRL);
}