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
struct uniphier_sd_priv {int clk_rate; int caps; int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; int /*<<< orphan*/  rst_br; } ;
struct tmio_mmc_host {struct mmc_host* mmc; } ;
struct mmc_host {int f_max; int f_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULONG_MAX ; 
 int UNIPHIER_SD_CAP_EXTENDED_IP ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 

__attribute__((used)) static int uniphier_sd_clk_enable(struct tmio_mmc_host *host)
{
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);
	struct mmc_host *mmc = host->mmc;
	int ret;

	ret = clk_prepare_enable(priv->clk);
	if (ret)
		return ret;

	ret = clk_set_rate(priv->clk, ULONG_MAX);
	if (ret)
		goto disable_clk;

	priv->clk_rate = clk_get_rate(priv->clk);

	/* If max-frequency property is set, use it. */
	if (!mmc->f_max)
		mmc->f_max = priv->clk_rate;

	/*
	 * 1/512 is the finest divisor in the original IP.  Newer versions
	 * also supports 1/1024 divisor. (UniPhier-specific extension)
	 */
	if (priv->caps & UNIPHIER_SD_CAP_EXTENDED_IP)
		mmc->f_min = priv->clk_rate / 1024;
	else
		mmc->f_min = priv->clk_rate / 512;

	ret = reset_control_deassert(priv->rst);
	if (ret)
		goto disable_clk;

	ret = reset_control_deassert(priv->rst_br);
	if (ret)
		goto assert_rst;

	return 0;

assert_rst:
	reset_control_assert(priv->rst);
disable_clk:
	clk_disable_unprepare(priv->clk);

	return ret;
}