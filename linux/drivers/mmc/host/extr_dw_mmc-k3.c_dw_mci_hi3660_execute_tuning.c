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
struct TYPE_2__ {int /*<<< orphan*/  timing; } ;
struct mmc_host {TYPE_1__ ios; } ;
struct dw_mci_slot {struct mmc_host* mmc; struct dw_mci* host; } ;
struct dw_mci {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int NUM_PHASES ; 
 int /*<<< orphan*/  TMOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int dw_mci_get_best_clksmpl (int) ; 
 int /*<<< orphan*/  dw_mci_hs_set_timing (struct dw_mci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_send_tuning (struct mmc_host*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw_mci_hi3660_execute_tuning(struct dw_mci_slot *slot, u32 opcode)
{
	int i = 0;
	struct dw_mci *host = slot->host;
	struct mmc_host *mmc = slot->mmc;
	int smpl_phase = 0;
	u32 tuning_sample_flag = 0;
	int best_clksmpl = 0;

	for (i = 0; i < NUM_PHASES; ++i, ++smpl_phase) {
		smpl_phase %= 32;

		mci_writel(host, TMOUT, ~0);
		dw_mci_hs_set_timing(host, mmc->ios.timing, smpl_phase);

		if (!mmc_send_tuning(mmc, opcode, NULL))
			tuning_sample_flag |= (1 << smpl_phase);
		else
			tuning_sample_flag &= ~(1 << smpl_phase);
	}

	best_clksmpl = dw_mci_get_best_clksmpl(tuning_sample_flag);
	if (best_clksmpl < 0) {
		dev_err(host->dev, "All phases bad!\n");
		return -EIO;
	}

	dw_mci_hs_set_timing(host, mmc->ios.timing, best_clksmpl);

	dev_info(host->dev, "tuning ok best_clksmpl %u tuning_sample_flag %x\n",
		 best_clksmpl, tuning_sample_flag);
	return 0;
}