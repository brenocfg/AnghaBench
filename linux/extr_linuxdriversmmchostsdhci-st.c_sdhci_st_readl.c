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
struct sdhci_host {int /*<<< orphan*/  ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_CAN_VDD_300 ; 
#define  SDHCI_CAPABILITIES 128 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 sdhci_st_readl(struct sdhci_host *host, int reg)
{
	u32 ret;

	switch (reg) {
	case SDHCI_CAPABILITIES:
		ret = readl_relaxed(host->ioaddr + reg);
		/* Support 3.3V and 1.8V */
		ret &= ~SDHCI_CAN_VDD_300;
		break;
	default:
		ret = readl_relaxed(host->ioaddr + reg);
	}
	return ret;
}