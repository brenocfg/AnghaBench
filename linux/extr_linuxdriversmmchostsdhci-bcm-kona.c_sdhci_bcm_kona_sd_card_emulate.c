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
typedef  int u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
struct sdhci_bcm_kona_dev {int /*<<< orphan*/  write_lock; } ;

/* Variables and functions */
 int KONA_SDHOST_CD_SW ; 
 int /*<<< orphan*/  KONA_SDHOST_CORESTAT ; 
 int KONA_SDHOST_WP ; 
 int mmc_gpio_get_ro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sdhci_bcm_kona_dev* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sdhci_bcm_kona_sd_card_emulate(struct sdhci_host *host, int insert)
{
	struct sdhci_pltfm_host *pltfm_priv = sdhci_priv(host);
	struct sdhci_bcm_kona_dev *kona_dev = sdhci_pltfm_priv(pltfm_priv);
	u32 val;

	/*
	 * Back-to-Back register write needs a delay of min 10uS.
	 * Back-to-Back writes to same register needs delay when SD bus clock
	 * is very low w.r.t AHB clock, mainly during boot-time and during card
	 * insert-removal.
	 * We keep 20uS
	 */
	mutex_lock(&kona_dev->write_lock);
	udelay(20);
	val = sdhci_readl(host, KONA_SDHOST_CORESTAT);

	if (insert) {
		int ret;

		ret = mmc_gpio_get_ro(host->mmc);
		if (ret >= 0)
			val = (val & ~KONA_SDHOST_WP) |
				((ret) ? KONA_SDHOST_WP : 0);

		val |= KONA_SDHOST_CD_SW;
		sdhci_writel(host, val, KONA_SDHOST_CORESTAT);
	} else {
		val &= ~KONA_SDHOST_CD_SW;
		sdhci_writel(host, val, KONA_SDHOST_CORESTAT);
	}
	mutex_unlock(&kona_dev->write_lock);

	return 0;
}