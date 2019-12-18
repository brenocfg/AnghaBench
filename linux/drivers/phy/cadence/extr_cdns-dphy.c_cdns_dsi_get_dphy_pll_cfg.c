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
typedef  unsigned long u64 ;
struct phy_configure_opts_mipi_dphy {unsigned long hs_clk_rate; } ;
struct cdns_dphy_cfg {int pll_ipdiv; int pll_opdiv; int /*<<< orphan*/  pll_fbdiv; } ;
struct cdns_dphy {int /*<<< orphan*/  pll_ref_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP_ULL (unsigned long,unsigned long) ; 
 int EINVAL ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cdns_dphy_cfg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cdns_dsi_get_dphy_pll_cfg(struct cdns_dphy *dphy,
				     struct cdns_dphy_cfg *cfg,
				     struct phy_configure_opts_mipi_dphy *opts,
				     unsigned int *dsi_hfp_ext)
{
	unsigned long pll_ref_hz = clk_get_rate(dphy->pll_ref_clk);
	u64 dlane_bps;

	memset(cfg, 0, sizeof(*cfg));

	if (pll_ref_hz < 9600000 || pll_ref_hz >= 150000000)
		return -EINVAL;
	else if (pll_ref_hz < 19200000)
		cfg->pll_ipdiv = 1;
	else if (pll_ref_hz < 38400000)
		cfg->pll_ipdiv = 2;
	else if (pll_ref_hz < 76800000)
		cfg->pll_ipdiv = 4;
	else
		cfg->pll_ipdiv = 8;

	dlane_bps = opts->hs_clk_rate;

	if (dlane_bps > 2500000000UL || dlane_bps < 160000000UL)
		return -EINVAL;
	else if (dlane_bps >= 1250000000)
		cfg->pll_opdiv = 1;
	else if (dlane_bps >= 630000000)
		cfg->pll_opdiv = 2;
	else if (dlane_bps >= 320000000)
		cfg->pll_opdiv = 4;
	else if (dlane_bps >= 160000000)
		cfg->pll_opdiv = 8;

	cfg->pll_fbdiv = DIV_ROUND_UP_ULL(dlane_bps * 2 * cfg->pll_opdiv *
					  cfg->pll_ipdiv,
					  pll_ref_hz);

	return 0;
}