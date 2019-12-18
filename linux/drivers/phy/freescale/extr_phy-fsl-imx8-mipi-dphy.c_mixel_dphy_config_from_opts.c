#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct phy_configure_opts_mipi_dphy {int hs_clk_rate; int lp_clk_rate; int hs_prepare; int clk_prepare; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct phy {TYPE_1__ dev; } ;
struct mixel_dphy_priv {int /*<<< orphan*/  phy_ref_clk; } ;
struct mixel_dphy_cfg {int cn; int co; int cm; int m_prg_hs_prepare; int mc_prg_hs_prepare; int m_prg_hs_zero; int mc_prg_hs_zero; int m_prg_hs_trail; int mc_prg_hs_trail; int rxhs_settle; } ;

/* Variables and functions */
 int DATA_RATE_MAX_SPEED ; 
 int DATA_RATE_MIN_SPEED ; 
 int EINVAL ; 
 int MBPS (int) ; 
 unsigned long long ULONG_MAX ; 
 int __ffs (int) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int,int,...) ; 
 struct mixel_dphy_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 int /*<<< orphan*/  get_best_ratio (int*,int*,int,int) ; 

__attribute__((used)) static int mixel_dphy_config_from_opts(struct phy *phy,
	       struct phy_configure_opts_mipi_dphy *dphy_opts,
	       struct mixel_dphy_cfg *cfg)
{
	struct mixel_dphy_priv *priv = dev_get_drvdata(phy->dev.parent);
	unsigned long ref_clk = clk_get_rate(priv->phy_ref_clk);
	u32 lp_t, numerator, denominator;
	unsigned long long tmp;
	u32 n;
	int i;

	if (dphy_opts->hs_clk_rate > DATA_RATE_MAX_SPEED ||
	    dphy_opts->hs_clk_rate < DATA_RATE_MIN_SPEED)
		return -EINVAL;

	numerator = dphy_opts->hs_clk_rate;
	denominator = ref_clk;
	get_best_ratio(&numerator, &denominator, 255, 256);
	if (!numerator || !denominator) {
		dev_err(&phy->dev, "Invalid %d/%d for %ld/%ld\n",
			numerator, denominator,
			dphy_opts->hs_clk_rate, ref_clk);
		return -EINVAL;
	}

	while ((numerator < 16) && (denominator <= 128)) {
		numerator <<= 1;
		denominator <<= 1;
	}
	/*
	 * CM ranges between 16 and 255
	 * CN ranges between 1 and 32
	 * CO is power of 2: 1, 2, 4, 8
	 */
	i = __ffs(denominator);
	if (i > 3)
		i = 3;
	cfg->cn = denominator >> i;
	cfg->co = 1 << i;
	cfg->cm = numerator;

	if (cfg->cm < 16 || cfg->cm > 255 ||
	    cfg->cn < 1 || cfg->cn > 32 ||
	    cfg->co < 1 || cfg->co > 8) {
		dev_err(&phy->dev, "Invalid CM/CN/CO values: %u/%u/%u\n",
			cfg->cm, cfg->cn, cfg->co);
		dev_err(&phy->dev, "for hs_clk/ref_clk=%ld/%ld ~ %d/%d\n",
			dphy_opts->hs_clk_rate, ref_clk,
			numerator, denominator);
		return -EINVAL;
	}

	dev_dbg(&phy->dev, "hs_clk/ref_clk=%ld/%ld ~ %d/%d\n",
		dphy_opts->hs_clk_rate, ref_clk, numerator, denominator);

	/* LP clock period */
	tmp = 1000000000000LL;
	do_div(tmp, dphy_opts->lp_clk_rate); /* ps */
	if (tmp > ULONG_MAX)
		return -EINVAL;

	lp_t = tmp;
	dev_dbg(&phy->dev, "LP clock %lu, period: %u ps\n",
		dphy_opts->lp_clk_rate, lp_t);

	/* hs_prepare: in lp clock periods */
	if (2 * dphy_opts->hs_prepare > 5 * lp_t) {
		dev_err(&phy->dev,
			"hs_prepare (%u) > 2.5 * lp clock period (%u)\n",
			dphy_opts->hs_prepare, lp_t);
		return -EINVAL;
	}
	/* 00: lp_t, 01: 1.5 * lp_t, 10: 2 * lp_t, 11: 2.5 * lp_t */
	if (dphy_opts->hs_prepare < lp_t) {
		n = 0;
	} else {
		tmp = 2 * (dphy_opts->hs_prepare - lp_t);
		do_div(tmp, lp_t);
		n = tmp;
	}
	cfg->m_prg_hs_prepare = n;

	/* clk_prepare: in lp clock periods */
	if (2 * dphy_opts->clk_prepare > 3 * lp_t) {
		dev_err(&phy->dev,
			"clk_prepare (%u) > 1.5 * lp clock period (%u)\n",
			dphy_opts->clk_prepare, lp_t);
		return -EINVAL;
	}
	/* 00: lp_t, 01: 1.5 * lp_t */
	cfg->mc_prg_hs_prepare = dphy_opts->clk_prepare > lp_t ? 1 : 0;

	/* hs_zero: formula from NXP BSP */
	n = (144 * (dphy_opts->hs_clk_rate / 1000000) - 47500) / 10000;
	cfg->m_prg_hs_zero = n < 1 ? 1 : n;

	/* clk_zero: formula from NXP BSP */
	n = (34 * (dphy_opts->hs_clk_rate / 1000000) - 2500) / 1000;
	cfg->mc_prg_hs_zero = n < 1 ? 1 : n;

	/* clk_trail, hs_trail: formula from NXP BSP */
	n = (103 * (dphy_opts->hs_clk_rate / 1000000) + 10000) / 10000;
	if (n > 15)
		n = 15;
	if (n < 1)
		n = 1;
	cfg->m_prg_hs_trail = n;
	cfg->mc_prg_hs_trail = n;

	/* rxhs_settle: formula from NXP BSP */
	if (dphy_opts->hs_clk_rate < MBPS(80))
		cfg->rxhs_settle = 0x0d;
	else if (dphy_opts->hs_clk_rate < MBPS(90))
		cfg->rxhs_settle = 0x0c;
	else if (dphy_opts->hs_clk_rate < MBPS(125))
		cfg->rxhs_settle = 0x0b;
	else if (dphy_opts->hs_clk_rate < MBPS(150))
		cfg->rxhs_settle = 0x0a;
	else if (dphy_opts->hs_clk_rate < MBPS(225))
		cfg->rxhs_settle = 0x09;
	else if (dphy_opts->hs_clk_rate < MBPS(500))
		cfg->rxhs_settle = 0x08;
	else
		cfg->rxhs_settle = 0x07;

	dev_dbg(&phy->dev, "phy_config: %u %u %u %u %u %u %u\n",
		cfg->m_prg_hs_prepare, cfg->mc_prg_hs_prepare,
		cfg->m_prg_hs_zero, cfg->mc_prg_hs_zero,
		cfg->m_prg_hs_trail, cfg->mc_prg_hs_trail,
		cfg->rxhs_settle);

	return 0;
}