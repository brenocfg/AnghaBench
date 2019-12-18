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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned char) ; 
 int XENON_SLOT_ENABLE_SHIFT ; 
 int /*<<< orphan*/  XENON_SYS_OP_CTRL ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xenon_disable_sdhc(struct sdhci_host *host,
			       unsigned char sdhc_id)
{
	u32 reg;

	reg = sdhci_readl(host, XENON_SYS_OP_CTRL);
	reg &= ~(BIT(sdhc_id) << XENON_SLOT_ENABLE_SHIFT);
	sdhci_writel(host, reg, XENON_SYS_OP_CTRL);
}