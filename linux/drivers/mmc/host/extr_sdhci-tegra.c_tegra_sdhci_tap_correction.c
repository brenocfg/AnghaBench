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
typedef  int u32 ;
struct sdhci_tegra {int tuned_tap_delay; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int tuning_loop_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_TEGRA_VNDR_TUN_STATUS0 ; 
 int /*<<< orphan*/  SDHCI_VNDR_TUN_CTRL0_0 ; 
 int SDHCI_VNDR_TUN_CTRL0_TUN_WORD_SEL_MASK ; 
 int TUNING_WORD_BIT_SIZE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sdhci_tap_correction(struct sdhci_host *host, u8 thd_up,
				       u8 thd_low, u8 fixed_tap)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	u32 val, tun_status;
	u8 word, bit, edge1, tap, window;
	bool tap_result;
	bool start_fail = false;
	bool start_pass = false;
	bool end_pass = false;
	bool first_fail = false;
	bool first_pass = false;
	u8 start_pass_tap = 0;
	u8 end_pass_tap = 0;
	u8 first_fail_tap = 0;
	u8 first_pass_tap = 0;
	u8 total_tuning_words = host->tuning_loop_count / TUNING_WORD_BIT_SIZE;

	/*
	 * Read auto-tuned results and extract good valid passing window by
	 * filtering out un-wanted bubble/partial/merged windows.
	 */
	for (word = 0; word < total_tuning_words; word++) {
		val = sdhci_readl(host, SDHCI_VNDR_TUN_CTRL0_0);
		val &= ~SDHCI_VNDR_TUN_CTRL0_TUN_WORD_SEL_MASK;
		val |= word;
		sdhci_writel(host, val, SDHCI_VNDR_TUN_CTRL0_0);
		tun_status = sdhci_readl(host, SDHCI_TEGRA_VNDR_TUN_STATUS0);
		bit = 0;
		while (bit < TUNING_WORD_BIT_SIZE) {
			tap = word * TUNING_WORD_BIT_SIZE + bit;
			tap_result = tun_status & (1 << bit);
			if (!tap_result && !start_fail) {
				start_fail = true;
				if (!first_fail) {
					first_fail_tap = tap;
					first_fail = true;
				}

			} else if (tap_result && start_fail && !start_pass) {
				start_pass_tap = tap;
				start_pass = true;
				if (!first_pass) {
					first_pass_tap = tap;
					first_pass = true;
				}

			} else if (!tap_result && start_fail && start_pass &&
				   !end_pass) {
				end_pass_tap = tap - 1;
				end_pass = true;
			} else if (tap_result && start_pass && start_fail &&
				   end_pass) {
				window = end_pass_tap - start_pass_tap;
				/* discard merged window and bubble window */
				if (window >= thd_up || window < thd_low) {
					start_pass_tap = tap;
					end_pass = false;
				} else {
					/* set tap at middle of valid window */
					tap = start_pass_tap + window / 2;
					tegra_host->tuned_tap_delay = tap;
					return;
				}
			}

			bit++;
		}
	}

	if (!first_fail) {
		WARN(1, "no edge detected, continue with hw tuned delay.\n");
	} else if (first_pass) {
		/* set tap location at fixed tap relative to the first edge */
		edge1 = first_fail_tap + (first_pass_tap - first_fail_tap) / 2;
		if (edge1 - 1 > fixed_tap)
			tegra_host->tuned_tap_delay = edge1 - fixed_tap;
		else
			tegra_host->tuned_tap_delay = edge1 + fixed_tap;
	}
}