#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* encoder; } ;
struct ti_sn_bridge {int /*<<< orphan*/  regmap; TYPE_5__* dsi; TYPE_4__ bridge; } ;
struct drm_display_mode {int clock; } ;
struct TYPE_10__ {int lanes; int /*<<< orphan*/  format; } ;
struct TYPE_8__ {TYPE_2__* crtc; } ;
struct TYPE_7__ {TYPE_1__* state; } ;
struct TYPE_6__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 unsigned int DP_CLK_FUDGE_DEN ; 
 unsigned int DP_CLK_FUDGE_NUM ; 
 int /*<<< orphan*/  DP_DATARATE (unsigned int) ; 
 int /*<<< orphan*/  DP_DATARATE_MASK ; 
 int MIN_DSI_CLK_FREQ_MHZ ; 
 int /*<<< orphan*/  SN_DATARATE_CONFIG_REG ; 
 int /*<<< orphan*/  SN_DSIA_CLK_FREQ_REG ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int* ti_sn_bridge_dp_rate_lut ; 

__attribute__((used)) static void ti_sn_bridge_set_dsi_dp_rate(struct ti_sn_bridge *pdata)
{
	unsigned int bit_rate_mhz, clk_freq_mhz, dp_rate_mhz;
	unsigned int val, i;
	struct drm_display_mode *mode =
		&pdata->bridge.encoder->crtc->state->adjusted_mode;

	/* set DSIA clk frequency */
	bit_rate_mhz = (mode->clock / 1000) *
			mipi_dsi_pixel_format_to_bpp(pdata->dsi->format);
	clk_freq_mhz = bit_rate_mhz / (pdata->dsi->lanes * 2);

	/* for each increment in val, frequency increases by 5MHz */
	val = (MIN_DSI_CLK_FREQ_MHZ / 5) +
		(((clk_freq_mhz - MIN_DSI_CLK_FREQ_MHZ) / 5) & 0xFF);
	regmap_write(pdata->regmap, SN_DSIA_CLK_FREQ_REG, val);

	/* set DP data rate */
	dp_rate_mhz = ((bit_rate_mhz / pdata->dsi->lanes) * DP_CLK_FUDGE_NUM) /
							DP_CLK_FUDGE_DEN;
	for (i = 0; i < ARRAY_SIZE(ti_sn_bridge_dp_rate_lut) - 1; i++)
		if (ti_sn_bridge_dp_rate_lut[i] > dp_rate_mhz)
			break;

	regmap_update_bits(pdata->regmap, SN_DATARATE_CONFIG_REG,
			   DP_DATARATE_MASK, DP_DATARATE(i));
}