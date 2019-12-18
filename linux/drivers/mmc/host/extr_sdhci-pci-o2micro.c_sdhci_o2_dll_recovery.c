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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_pci_slot {struct sdhci_pci_chip* chip; } ;
struct sdhci_pci_chip {int /*<<< orphan*/  pdev; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
struct o2_host {size_t dll_adjust_count; } ;

/* Variables and functions */
 size_t DMDN_SZ ; 
 int /*<<< orphan*/  O2_PLL_DLL_WDT_CONTROL1 ; 
 int /*<<< orphan*/  O2_PLL_SOFT_RESET ; 
 int /*<<< orphan*/  O2_SD_FREG4_ENABLE_CLK_SET ; 
 int /*<<< orphan*/  O2_SD_FUNC_REG4 ; 
 int /*<<< orphan*/  O2_SD_LOCK_WP ; 
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int SDHCI_CLOCK_INT_EN ; 
 int /*<<< orphan*/ * dmdn_table ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2_pci_set_baseclk (struct sdhci_pci_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sdhci_o2_get_cd (int /*<<< orphan*/ ) ; 
 scalar_t__ sdhci_o2_wait_dll_detect_lock (struct sdhci_host*) ; 
 struct o2_host* sdhci_pci_priv (struct sdhci_pci_slot*) ; 
 struct sdhci_pci_slot* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sdhci_o2_dll_recovery(struct sdhci_host *host)
{
	int ret = 0;
	u8 scratch_8 = 0;
	u32 scratch_32 = 0;
	struct sdhci_pci_slot *slot = sdhci_priv(host);
	struct sdhci_pci_chip *chip = slot->chip;
	struct o2_host *o2_host = sdhci_pci_priv(slot);

	/* UnLock WP */
	pci_read_config_byte(chip->pdev,
			O2_SD_LOCK_WP, &scratch_8);
	scratch_8 &= 0x7f;
	pci_write_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch_8);
	while (o2_host->dll_adjust_count < DMDN_SZ && !ret) {
		/* Disable clock */
		sdhci_writeb(host, 0, SDHCI_CLOCK_CONTROL);

		/* PLL software reset */
		scratch_32 = sdhci_readl(host, O2_PLL_DLL_WDT_CONTROL1);
		scratch_32 |= O2_PLL_SOFT_RESET;
		sdhci_writel(host, scratch_32, O2_PLL_DLL_WDT_CONTROL1);

		pci_read_config_dword(chip->pdev,
					    O2_SD_FUNC_REG4,
					    &scratch_32);
		/* Enable Base Clk setting change */
		scratch_32 |= O2_SD_FREG4_ENABLE_CLK_SET;
		pci_write_config_dword(chip->pdev, O2_SD_FUNC_REG4, scratch_32);
		o2_pci_set_baseclk(chip, dmdn_table[o2_host->dll_adjust_count]);

		/* Enable internal clock */
		scratch_8 = SDHCI_CLOCK_INT_EN;
		sdhci_writeb(host, scratch_8, SDHCI_CLOCK_CONTROL);

		if (sdhci_o2_get_cd(host->mmc)) {
			/*
			 * need wait at least 5ms for dll status stable,
			 * after enable internal clock
			 */
			usleep_range(5000, 6000);
			if (sdhci_o2_wait_dll_detect_lock(host)) {
				scratch_8 |= SDHCI_CLOCK_CARD_EN;
				sdhci_writeb(host, scratch_8,
					SDHCI_CLOCK_CONTROL);
				ret = 1;
			} else {
				pr_warn("%s: DLL unlocked when dll_adjust_count is %d.\n",
					mmc_hostname(host->mmc),
					o2_host->dll_adjust_count);
			}
		} else {
			pr_err("%s: card present detect failed.\n",
				mmc_hostname(host->mmc));
			break;
		}

		o2_host->dll_adjust_count++;
	}
	if (!ret && o2_host->dll_adjust_count == DMDN_SZ)
		pr_err("%s: DLL adjust over max times\n",
		mmc_hostname(host->mmc));
	/* Lock WP */
	pci_read_config_byte(chip->pdev,
				   O2_SD_LOCK_WP, &scratch_8);
	scratch_8 |= 0x80;
	pci_write_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch_8);
	return ret;
}