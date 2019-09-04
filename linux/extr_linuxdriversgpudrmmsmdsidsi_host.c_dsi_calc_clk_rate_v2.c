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
typedef  int u64 ;
typedef  int u32 ;
struct msm_dsi_host {int src_clk_rate; int byte_clk_rate; unsigned int esc_clk_rate; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned int,int) ; 
 unsigned int DIV_ROUND_UP (unsigned long,unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  dsi_calc_pclk (struct msm_dsi_host*,int) ; 
 int dsi_get_bpp (int /*<<< orphan*/ ) ; 
 scalar_t__ dsi_get_pclk_rate (struct msm_dsi_host*,int) ; 

int dsi_calc_clk_rate_v2(struct msm_dsi_host *msm_host, bool is_dual_dsi)
{
	u32 bpp = dsi_get_bpp(msm_host->format);
	u64 pclk_bpp;
	unsigned int esc_mhz, esc_div;
	unsigned long byte_mhz;

	dsi_calc_pclk(msm_host, is_dual_dsi);

	pclk_bpp = (u64)dsi_get_pclk_rate(msm_host, is_dual_dsi) * bpp;
	do_div(pclk_bpp, 8);
	msm_host->src_clk_rate = pclk_bpp;

	/*
	 * esc clock is byte clock followed by a 4 bit divider,
	 * we need to find an escape clock frequency within the
	 * mipi DSI spec range within the maximum divider limit
	 * We iterate here between an escape clock frequencey
	 * between 20 Mhz to 5 Mhz and pick up the first one
	 * that can be supported by our divider
	 */

	byte_mhz = msm_host->byte_clk_rate / 1000000;

	for (esc_mhz = 20; esc_mhz >= 5; esc_mhz--) {
		esc_div = DIV_ROUND_UP(byte_mhz, esc_mhz);

		/*
		 * TODO: Ideally, we shouldn't know what sort of divider
		 * is available in mmss_cc, we're just assuming that
		 * it'll always be a 4 bit divider. Need to come up with
		 * a better way here.
		 */
		if (esc_div >= 1 && esc_div <= 16)
			break;
	}

	if (esc_mhz < 5)
		return -EINVAL;

	msm_host->esc_clk_rate = msm_host->byte_clk_rate / esc_div;

	DBG("esc=%d, src=%d", msm_host->esc_clk_rate,
		msm_host->src_clk_rate);

	return 0;
}