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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_host {scalar_t__ doing_retune; } ;
struct meson_host {TYPE_1__* data; scalar_t__ regs; int /*<<< orphan*/  mmc_clk; int /*<<< orphan*/  mux_clk; } ;
struct TYPE_2__ {scalar_t__ adjust; } ;

/* Variables and functions */
 unsigned int ADJUST_ADJ_DELAY_MASK ; 
 unsigned int ADJUST_ADJ_EN ; 
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int FIELD_GET (unsigned int,unsigned int) ; 
 unsigned int FIELD_PREP (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  meson_mmc_reset_resampling (struct meson_host*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 struct meson_host* mmc_priv (struct mmc_host*) ; 
 int mmc_send_tuning (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int meson_mmc_resampling_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct meson_host *host = mmc_priv(mmc);
	unsigned int val, dly, max_dly, i;
	int ret;

	/* Resampling is done using the source clock */
	max_dly = DIV_ROUND_UP(clk_get_rate(host->mux_clk),
			       clk_get_rate(host->mmc_clk));

	val = readl(host->regs + host->data->adjust);
	val |= ADJUST_ADJ_EN;
	writel(val, host->regs + host->data->adjust);

	if (mmc->doing_retune)
		dly = FIELD_GET(ADJUST_ADJ_DELAY_MASK, val) + 1;
	else
		dly = 0;

	for (i = 0; i < max_dly; i++) {
		val &= ~ADJUST_ADJ_DELAY_MASK;
		val |= FIELD_PREP(ADJUST_ADJ_DELAY_MASK, (dly + i) % max_dly);
		writel(val, host->regs + host->data->adjust);

		ret = mmc_send_tuning(mmc, opcode, NULL);
		if (!ret) {
			dev_dbg(mmc_dev(mmc), "resampling delay: %u\n",
				(dly + i) % max_dly);
			return 0;
		}
	}

	meson_mmc_reset_resampling(host);
	return -EIO;
}