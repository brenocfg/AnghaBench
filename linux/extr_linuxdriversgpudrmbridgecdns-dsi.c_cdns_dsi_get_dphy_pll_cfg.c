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
typedef  unsigned int u64 ;
typedef  scalar_t__ u32 ;
struct cdns_dphy_cfg {unsigned int nlanes; int pll_ipdiv; int pll_opdiv; unsigned int pll_fbdiv; unsigned int lane_bps; } ;
struct cdns_dphy {int /*<<< orphan*/  pll_ref_clk; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_DOWN_ULL (unsigned int,unsigned int) ; 
 unsigned int DIV_ROUND_UP_ULL (unsigned int,unsigned long) ; 
 int EINVAL ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ do_div (unsigned int,int) ; 
 int /*<<< orphan*/  memset (struct cdns_dphy_cfg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cdns_dsi_get_dphy_pll_cfg(struct cdns_dphy *dphy,
				     struct cdns_dphy_cfg *cfg,
				     unsigned int dpi_htotal,
				     unsigned int dpi_bpp,
				     unsigned int dpi_hz,
				     unsigned int dsi_htotal,
				     unsigned int dsi_nlanes,
				     unsigned int *dsi_hfp_ext)
{
	u64 dlane_bps, dlane_bps_max, fbdiv, fbdiv_max, adj_dsi_htotal;
	unsigned long pll_ref_hz = clk_get_rate(dphy->pll_ref_clk);

	memset(cfg, 0, sizeof(*cfg));

	cfg->nlanes = dsi_nlanes;

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

	/*
	 * Make sure DSI htotal is aligned on a lane boundary when calculating
	 * the expected data rate. This is done by extending HFP in case of
	 * misalignment.
	 */
	adj_dsi_htotal = dsi_htotal;
	if (dsi_htotal % dsi_nlanes)
		adj_dsi_htotal += dsi_nlanes - (dsi_htotal % dsi_nlanes);

	dlane_bps = (u64)dpi_hz * adj_dsi_htotal;

	/* data rate in bytes/sec is not an integer, refuse the mode. */
	if (do_div(dlane_bps, dsi_nlanes * dpi_htotal))
		return -EINVAL;

	/* data rate was in bytes/sec, convert to bits/sec. */
	dlane_bps *= 8;

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

	/*
	 * Allow a deviation of 0.2% on the per-lane data rate to try to
	 * recover a potential mismatch between DPI and PPI clks.
	 */
	dlane_bps_max = dlane_bps + DIV_ROUND_DOWN_ULL(dlane_bps, 500);
	fbdiv_max = DIV_ROUND_DOWN_ULL(dlane_bps_max * 2 *
				       cfg->pll_opdiv * cfg->pll_ipdiv,
				       pll_ref_hz);
	fbdiv = DIV_ROUND_UP_ULL(dlane_bps * 2 * cfg->pll_opdiv *
				 cfg->pll_ipdiv,
				 pll_ref_hz);

	/*
	 * Iterate over all acceptable fbdiv and try to find an adjusted DSI
	 * htotal length providing an exact match.
	 *
	 * Note that we could do something even trickier by relying on the fact
	 * that a new line is not necessarily aligned on a lane boundary, so,
	 * by making adj_dsi_htotal non aligned on a dsi_lanes we can improve a
	 * bit the precision. With this, the step would be
	 *
	 *	pll_ref_hz / (2 * opdiv * ipdiv * nlanes)
	 *
	 * instead of
	 *
	 *	pll_ref_hz / (2 * opdiv * ipdiv)
	 *
	 * The drawback of this approach is that we would need to make sure the
	 * number or lines is a multiple of the realignment periodicity which is
	 * a function of the number of lanes and the original misalignment. For
	 * example, for NLANES = 4 and HTOTAL % NLANES = 3, it takes 4 lines
	 * to realign on a lane:
	 * LINE 0: expected number of bytes, starts emitting first byte of
	 *	   LINE 1 on LANE 3
	 * LINE 1: expected number of bytes, starts emitting first 2 bytes of
	 *	   LINE 2 on LANES 2 and 3
	 * LINE 2: expected number of bytes, starts emitting first 3 bytes of
	 *	   of LINE 3 on LANES 1, 2 and 3
	 * LINE 3: one byte less, now things are realigned on LANE 0 for LINE 4
	 *
	 * I figured this extra complexity was not worth the benefit, but if
	 * someone really has unfixable mismatch, that would be something to
	 * investigate.
	 */
	for (; fbdiv <= fbdiv_max; fbdiv++) {
		u32 rem;

		adj_dsi_htotal = (u64)fbdiv * pll_ref_hz * dsi_nlanes *
				 dpi_htotal;

		/*
		 * Do the division in 2 steps to avoid an overflow on the
		 * divider.
		 */
		rem = do_div(adj_dsi_htotal, dpi_hz);
		if (rem)
			continue;

		rem = do_div(adj_dsi_htotal,
			     cfg->pll_opdiv * cfg->pll_ipdiv * 2 * 8);
		if (rem)
			continue;

		cfg->pll_fbdiv = fbdiv;
		*dsi_hfp_ext = adj_dsi_htotal - dsi_htotal;
		break;
	}

	/* No match, let's just reject the display mode. */
	if (!cfg->pll_fbdiv)
		return -EINVAL;

	dlane_bps = DIV_ROUND_DOWN_ULL((u64)dpi_hz * adj_dsi_htotal * 8,
				       dsi_nlanes * dpi_htotal);
	cfg->lane_bps = dlane_bps;

	return 0;
}