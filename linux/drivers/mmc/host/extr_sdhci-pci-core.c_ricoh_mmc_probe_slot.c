#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sdhci_pci_slot {TYPE_1__* host; } ;
struct TYPE_2__ {int caps; } ;

/* Variables and functions */
 int SDHCI_CAN_DO_HISPD ; 
 int SDHCI_CAN_DO_SDMA ; 
 int SDHCI_CAN_VDD_330 ; 
 int SDHCI_CLOCK_BASE_MASK ; 
 int SDHCI_CLOCK_BASE_SHIFT ; 
 int SDHCI_TIMEOUT_CLK_MASK ; 
 int SDHCI_TIMEOUT_CLK_SHIFT ; 
 int SDHCI_TIMEOUT_CLK_UNIT ; 

__attribute__((used)) static int ricoh_mmc_probe_slot(struct sdhci_pci_slot *slot)
{
	slot->host->caps =
		((0x21 << SDHCI_TIMEOUT_CLK_SHIFT)
			& SDHCI_TIMEOUT_CLK_MASK) |

		((0x21 << SDHCI_CLOCK_BASE_SHIFT)
			& SDHCI_CLOCK_BASE_MASK) |

		SDHCI_TIMEOUT_CLK_UNIT |
		SDHCI_CAN_VDD_330 |
		SDHCI_CAN_DO_HISPD |
		SDHCI_CAN_DO_SDMA;
	return 0;
}