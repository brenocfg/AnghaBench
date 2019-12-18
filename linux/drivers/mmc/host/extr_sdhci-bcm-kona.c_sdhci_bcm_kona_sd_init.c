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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KONA_SDHOST_CORECTRL ; 
 int /*<<< orphan*/  KONA_SDHOST_COREIMR ; 
 unsigned int KONA_SDHOST_EN ; 
 unsigned int KONA_SDHOST_IP ; 
 unsigned int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void sdhci_bcm_kona_sd_init(struct sdhci_host *host)
{
	unsigned int val;

	/* enable the interrupt from the IP core */
	val = sdhci_readl(host, KONA_SDHOST_COREIMR);
	val |= KONA_SDHOST_IP;
	sdhci_writel(host, val, KONA_SDHOST_COREIMR);

	/* Enable the AHB clock gating module to the host */
	val = sdhci_readl(host, KONA_SDHOST_CORECTRL);
	val |= KONA_SDHOST_EN;

	/*
	 * Back-to-Back register write needs a delay of 1ms at bootup (min 10uS)
	 * Back-to-Back writes to same register needs delay when SD bus clock
	 * is very low w.r.t AHB clock, mainly during boot-time and during card
	 * insert-removal.
	 */
	usleep_range(1000, 5000);
	sdhci_writel(host, val, KONA_SDHOST_CORECTRL);
}