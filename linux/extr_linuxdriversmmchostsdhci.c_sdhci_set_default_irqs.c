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
struct sdhci_host {int ier; scalar_t__ tuning_mode; } ;

/* Variables and functions */
 int SDHCI_INT_BUS_POWER ; 
 int SDHCI_INT_CRC ; 
 int SDHCI_INT_DATA_CRC ; 
 int SDHCI_INT_DATA_END ; 
 int SDHCI_INT_DATA_END_BIT ; 
 int SDHCI_INT_DATA_TIMEOUT ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int SDHCI_INT_END_BIT ; 
 int SDHCI_INT_INDEX ; 
 int SDHCI_INT_RESPONSE ; 
 int SDHCI_INT_RETUNE ; 
 int SDHCI_INT_TIMEOUT ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 scalar_t__ SDHCI_TUNING_MODE_2 ; 
 scalar_t__ SDHCI_TUNING_MODE_3 ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_set_default_irqs(struct sdhci_host *host)
{
	host->ier = SDHCI_INT_BUS_POWER | SDHCI_INT_DATA_END_BIT |
		    SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_TIMEOUT |
		    SDHCI_INT_INDEX | SDHCI_INT_END_BIT | SDHCI_INT_CRC |
		    SDHCI_INT_TIMEOUT | SDHCI_INT_DATA_END |
		    SDHCI_INT_RESPONSE;

	if (host->tuning_mode == SDHCI_TUNING_MODE_2 ||
	    host->tuning_mode == SDHCI_TUNING_MODE_3)
		host->ier |= SDHCI_INT_RETUNE;

	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}