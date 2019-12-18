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
 int EFAULT ; 
 int /*<<< orphan*/  KONA_SDHOST_CORECTRL ; 
 unsigned int KONA_SDHOST_RESET ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 unsigned int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sdhci_bcm_kona_sd_reset(struct sdhci_host *host)
{
	unsigned int val;
	unsigned long timeout;

	/* This timeout should be sufficent for core to reset */
	timeout = jiffies + msecs_to_jiffies(100);

	/* reset the host using the top level reset */
	val = sdhci_readl(host, KONA_SDHOST_CORECTRL);
	val |= KONA_SDHOST_RESET;
	sdhci_writel(host, val, KONA_SDHOST_CORECTRL);

	while (!(sdhci_readl(host, KONA_SDHOST_CORECTRL) & KONA_SDHOST_RESET)) {
		if (time_is_before_jiffies(timeout)) {
			pr_err("Error: sd host is stuck in reset!!!\n");
			return -EFAULT;
		}
	}

	/* bring the host out of reset */
	val = sdhci_readl(host, KONA_SDHOST_CORECTRL);
	val &= ~KONA_SDHOST_RESET;

	/*
	 * Back-to-Back register write needs a delay of 1ms at bootup (min 10uS)
	 * Back-to-Back writes to same register needs delay when SD bus clock
	 * is very low w.r.t AHB clock, mainly during boot-time and during card
	 * insert-removal.
	 */
	usleep_range(1000, 5000);
	sdhci_writel(host, val, KONA_SDHOST_CORECTRL);

	return 0;
}