#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mipi_config {int tclk_prepare_clkzero; int ths_prepare_hszero; int ths_prepare; int tclk_prepare; int tclk_trail; int ths_trail; } ;
struct TYPE_5__ {struct drm_device* dev; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct intel_dsi {int lane_count; int dphy_reg; void* clk_hs_to_lp_count; void* clk_lp_to_hs_count; void* hs_to_lp_count; void* lp_byte_clk; TYPE_2__ base; } ;
struct TYPE_7__ {struct mipi_config* config; } ;
struct TYPE_8__ {TYPE_3__ dsi; } ;
struct drm_i915_private {TYPE_4__ vbt; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int CLK_ZERO_CNT_MAX ; 
 void* DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int EXIT_ZERO_CNT_MAX ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int NS_KHZ_RATIO ; 
 int PREPARE_CNT_MAX ; 
 int TRAIL_CNT_MAX ; 
 int intel_dsi_bitrate (struct intel_dsi*) ; 
 int /*<<< orphan*/  intel_dsi_log_params (struct intel_dsi*) ; 
 int intel_dsi_tlpx_ns (struct intel_dsi*) ; 
 void* max (int,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void vlv_dphy_param_init(struct intel_dsi *intel_dsi)
{
	struct drm_device *dev = intel_dsi->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct mipi_config *mipi_config = dev_priv->vbt.dsi.config;
	u32 tlpx_ns, extra_byte_count, tlpx_ui;
	u32 ui_num, ui_den;
	u32 prepare_cnt, exit_zero_cnt, clk_zero_cnt, trail_cnt;
	u32 ths_prepare_ns, tclk_trail_ns;
	u32 tclk_prepare_clkzero, ths_prepare_hszero;
	u32 lp_to_hs_switch, hs_to_lp_switch;
	u32 mul;

	tlpx_ns = intel_dsi_tlpx_ns(intel_dsi);

	switch (intel_dsi->lane_count) {
	case 1:
	case 2:
		extra_byte_count = 2;
		break;
	case 3:
		extra_byte_count = 4;
		break;
	case 4:
	default:
		extra_byte_count = 3;
		break;
	}

	/* in Kbps */
	ui_num = NS_KHZ_RATIO;
	ui_den = intel_dsi_bitrate(intel_dsi);

	tclk_prepare_clkzero = mipi_config->tclk_prepare_clkzero;
	ths_prepare_hszero = mipi_config->ths_prepare_hszero;

	/*
	 * B060
	 * LP byte clock = TLPX/ (8UI)
	 */
	intel_dsi->lp_byte_clk = DIV_ROUND_UP(tlpx_ns * ui_den, 8 * ui_num);

	/* DDR clock period = 2 * UI
	 * UI(sec) = 1/(bitrate * 10^3) (bitrate is in KHZ)
	 * UI(nsec) = 10^6 / bitrate
	 * DDR clock period (nsec) = 2 * UI = (2 * 10^6)/ bitrate
	 * DDR clock count  = ns_value / DDR clock period
	 *
	 * For GEMINILAKE dphy_param_reg will be programmed in terms of
	 * HS byte clock count for other platform in HS ddr clock count
	 */
	mul = IS_GEMINILAKE(dev_priv) ? 8 : 2;
	ths_prepare_ns = max(mipi_config->ths_prepare,
			     mipi_config->tclk_prepare);

	/* prepare count */
	prepare_cnt = DIV_ROUND_UP(ths_prepare_ns * ui_den, ui_num * mul);

	if (prepare_cnt > PREPARE_CNT_MAX) {
		DRM_DEBUG_KMS("prepare count too high %u\n", prepare_cnt);
		prepare_cnt = PREPARE_CNT_MAX;
	}

	/* exit zero count */
	exit_zero_cnt = DIV_ROUND_UP(
				(ths_prepare_hszero - ths_prepare_ns) * ui_den,
				ui_num * mul
				);

	/*
	 * Exit zero is unified val ths_zero and ths_exit
	 * minimum value for ths_exit = 110ns
	 * min (exit_zero_cnt * 2) = 110/UI
	 * exit_zero_cnt = 55/UI
	 */
	if (exit_zero_cnt < (55 * ui_den / ui_num) && (55 * ui_den) % ui_num)
		exit_zero_cnt += 1;

	if (exit_zero_cnt > EXIT_ZERO_CNT_MAX) {
		DRM_DEBUG_KMS("exit zero count too high %u\n", exit_zero_cnt);
		exit_zero_cnt = EXIT_ZERO_CNT_MAX;
	}

	/* clk zero count */
	clk_zero_cnt = DIV_ROUND_UP(
				(tclk_prepare_clkzero -	ths_prepare_ns)
				* ui_den, ui_num * mul);

	if (clk_zero_cnt > CLK_ZERO_CNT_MAX) {
		DRM_DEBUG_KMS("clock zero count too high %u\n", clk_zero_cnt);
		clk_zero_cnt = CLK_ZERO_CNT_MAX;
	}

	/* trail count */
	tclk_trail_ns = max(mipi_config->tclk_trail, mipi_config->ths_trail);
	trail_cnt = DIV_ROUND_UP(tclk_trail_ns * ui_den, ui_num * mul);

	if (trail_cnt > TRAIL_CNT_MAX) {
		DRM_DEBUG_KMS("trail count too high %u\n", trail_cnt);
		trail_cnt = TRAIL_CNT_MAX;
	}

	/* B080 */
	intel_dsi->dphy_reg = exit_zero_cnt << 24 | trail_cnt << 16 |
						clk_zero_cnt << 8 | prepare_cnt;

	/*
	 * LP to HS switch count = 4TLPX + PREP_COUNT * mul + EXIT_ZERO_COUNT *
	 *					mul + 10UI + Extra Byte Count
	 *
	 * HS to LP switch count = THS-TRAIL + 2TLPX + Extra Byte Count
	 * Extra Byte Count is calculated according to number of lanes.
	 * High Low Switch Count is the Max of LP to HS and
	 * HS to LP switch count
	 *
	 */
	tlpx_ui = DIV_ROUND_UP(tlpx_ns * ui_den, ui_num);

	/* B044 */
	/* FIXME:
	 * The comment above does not match with the code */
	lp_to_hs_switch = DIV_ROUND_UP(4 * tlpx_ui + prepare_cnt * mul +
						exit_zero_cnt * mul + 10, 8);

	hs_to_lp_switch = DIV_ROUND_UP(mipi_config->ths_trail + 2 * tlpx_ui, 8);

	intel_dsi->hs_to_lp_count = max(lp_to_hs_switch, hs_to_lp_switch);
	intel_dsi->hs_to_lp_count += extra_byte_count;

	/* B088 */
	/* LP -> HS for clock lanes
	 * LP clk sync + LP11 + LP01 + tclk_prepare + tclk_zero +
	 *						extra byte count
	 * 2TPLX + 1TLPX + 1 TPLX(in ns) + prepare_cnt * 2 + clk_zero_cnt *
	 *					2(in UI) + extra byte count
	 * In byteclks = (4TLPX + prepare_cnt * 2 + clk_zero_cnt *2 (in UI)) /
	 *					8 + extra byte count
	 */
	intel_dsi->clk_lp_to_hs_count =
		DIV_ROUND_UP(
			4 * tlpx_ui + prepare_cnt * 2 +
			clk_zero_cnt * 2,
			8);

	intel_dsi->clk_lp_to_hs_count += extra_byte_count;

	/* HS->LP for Clock Lanes
	 * Low Power clock synchronisations + 1Tx byteclk + tclk_trail +
	 *						Extra byte count
	 * 2TLPX + 8UI + (trail_count*2)(in UI) + Extra byte count
	 * In byteclks = (2*TLpx(in UI) + trail_count*2 +8)(in UI)/8 +
	 *						Extra byte count
	 */
	intel_dsi->clk_hs_to_lp_count =
		DIV_ROUND_UP(2 * tlpx_ui + trail_cnt * 2 + 8,
			8);
	intel_dsi->clk_hs_to_lp_count += extra_byte_count;

	intel_dsi_log_params(intel_dsi);
}