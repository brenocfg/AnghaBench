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
 scalar_t__ ESDHC_CAPABILITIES_1 ; 
 int SDHCI_CAPABILITIES_1 ; 
 int /*<<< orphan*/  esdhc_readl_fixup (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32be (scalar_t__) ; 

__attribute__((used)) static u32 esdhc_be_readl(struct sdhci_host *host, int reg)
{
	u32 ret;
	u32 value;

	if (reg == SDHCI_CAPABILITIES_1)
		value = ioread32be(host->ioaddr + ESDHC_CAPABILITIES_1);
	else
		value = ioread32be(host->ioaddr + reg);

	ret = esdhc_readl_fixup(host, reg, value);

	return ret;
}