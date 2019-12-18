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
struct tmio_mmc_host {struct mmc_host* mmc; } ;
struct renesas_sdhi {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_cd; } ;
struct mmc_host {int /*<<< orphan*/  f_min; scalar_t__ f_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_round_rate (int /*<<< orphan*/ ,int) ; 
 struct renesas_sdhi* host_to_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  max (int,long) ; 
 int /*<<< orphan*/  renesas_sdhi_sdbuf_width (struct tmio_mmc_host*,int) ; 

__attribute__((used)) static int renesas_sdhi_clk_enable(struct tmio_mmc_host *host)
{
	struct mmc_host *mmc = host->mmc;
	struct renesas_sdhi *priv = host_to_priv(host);
	int ret = clk_prepare_enable(priv->clk);

	if (ret < 0)
		return ret;

	ret = clk_prepare_enable(priv->clk_cd);
	if (ret < 0) {
		clk_disable_unprepare(priv->clk);
		return ret;
	}

	/*
	 * The clock driver may not know what maximum frequency
	 * actually works, so it should be set with the max-frequency
	 * property which will already have been read to f_max.  If it
	 * was missing, assume the current frequency is the maximum.
	 */
	if (!mmc->f_max)
		mmc->f_max = clk_get_rate(priv->clk);

	/*
	 * Minimum frequency is the minimum input clock frequency
	 * divided by our maximum divider.
	 */
	mmc->f_min = max(clk_round_rate(priv->clk, 1) / 512, 1L);

	/* enable 16bit data access on SDBUF as default */
	renesas_sdhi_sdbuf_width(host, 16);

	return 0;
}