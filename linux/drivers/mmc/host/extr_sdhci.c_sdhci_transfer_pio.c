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
struct sdhci_host {scalar_t__ blocks; int quirks; TYPE_1__* data; } ;
struct TYPE_2__ {int flags; int blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int MMC_DATA_READ ; 
 int SDHCI_DATA_AVAILABLE ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int SDHCI_QUIRK_BROKEN_SMALL_PIO ; 
 int SDHCI_QUIRK_PIO_NEEDS_DELAY ; 
 int SDHCI_SPACE_AVAILABLE ; 
 int /*<<< orphan*/  sdhci_read_block_pio (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_write_block_pio (struct sdhci_host*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sdhci_transfer_pio(struct sdhci_host *host)
{
	u32 mask;

	if (host->blocks == 0)
		return;

	if (host->data->flags & MMC_DATA_READ)
		mask = SDHCI_DATA_AVAILABLE;
	else
		mask = SDHCI_SPACE_AVAILABLE;

	/*
	 * Some controllers (JMicron JMB38x) mess up the buffer bits
	 * for transfers < 4 bytes. As long as it is just one block,
	 * we can ignore the bits.
	 */
	if ((host->quirks & SDHCI_QUIRK_BROKEN_SMALL_PIO) &&
		(host->data->blocks == 1))
		mask = ~0;

	while (sdhci_readl(host, SDHCI_PRESENT_STATE) & mask) {
		if (host->quirks & SDHCI_QUIRK_PIO_NEEDS_DELAY)
			udelay(100);

		if (host->data->flags & MMC_DATA_READ)
			sdhci_read_block_pio(host);
		else
			sdhci_write_block_pio(host);

		host->blocks--;
		if (host->blocks == 0)
			break;
	}

	DBG("PIO transfer complete.\n");
}