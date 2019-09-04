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
 int /*<<< orphan*/  SDHCI_CAN_VDD_300 ; 
#define  SDHCI_CAPABILITIES 128 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static u32 sdhci_dove_readl(struct sdhci_host *host, int reg)
{
	u32 ret;

	ret = readl(host->ioaddr + reg);

	switch (reg) {
	case SDHCI_CAPABILITIES:
		/* Mask the support for 3.0V */
		ret &= ~SDHCI_CAN_VDD_300;
		break;
	}
	return ret;
}