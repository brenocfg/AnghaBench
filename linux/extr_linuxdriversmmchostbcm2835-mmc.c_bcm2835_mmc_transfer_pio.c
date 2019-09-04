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
typedef  int u32 ;
struct bcm2835_host {scalar_t__ blocks; TYPE_1__* data; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MMC_DATA_READ ; 
 int SDHCI_DATA_AVAILABLE ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int SDHCI_SPACE_AVAILABLE ; 
 int /*<<< orphan*/  bcm2835_bcm2835_mmc_read_block_pio (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_bcm2835_mmc_write_block_pio (struct bcm2835_host*) ; 
 int bcm2835_mmc_readl (struct bcm2835_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_mmc_transfer_pio(struct bcm2835_host *host)
{
	u32 mask;

	BUG_ON(!host->data);

	if (host->blocks == 0)
		return;

	if (host->data->flags & MMC_DATA_READ)
		mask = SDHCI_DATA_AVAILABLE;
	else
		mask = SDHCI_SPACE_AVAILABLE;

	while (bcm2835_mmc_readl(host, SDHCI_PRESENT_STATE) & mask) {

		if (host->data->flags & MMC_DATA_READ)
			bcm2835_bcm2835_mmc_read_block_pio(host);
		else
			bcm2835_bcm2835_mmc_write_block_pio(host);

		host->blocks--;

		/* QUIRK used in sdhci.c removes the 'if' */
		/* but it seems this is unnecessary */
		if (host->blocks == 0)
			break;


	}
}