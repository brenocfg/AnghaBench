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
typedef  scalar_t__ u32 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ MMC_WRITE_MULTIPLE_BLOCK ; 
 int /*<<< orphan*/  SDHCI_BLOCK_COUNT ; 
 int /*<<< orphan*/  SDHCI_COMMAND ; 
 scalar_t__ SDHCI_GET_CMD (scalar_t__) ; 
 scalar_t__ SDHCI_INT_DATA_END ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 scalar_t__ of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 esdhc_irq(struct sdhci_host *host, u32 intmask)
{
	u32 command;

	if (of_find_compatible_node(NULL, NULL,
				"fsl,p2020-esdhc")) {
		command = SDHCI_GET_CMD(sdhci_readw(host,
					SDHCI_COMMAND));
		if (command == MMC_WRITE_MULTIPLE_BLOCK &&
				sdhci_readw(host, SDHCI_BLOCK_COUNT) &&
				intmask & SDHCI_INT_DATA_END) {
			intmask &= ~SDHCI_INT_DATA_END;
			sdhci_writel(host, SDHCI_INT_DATA_END,
					SDHCI_INT_STATUS);
		}
	}
	return intmask;
}