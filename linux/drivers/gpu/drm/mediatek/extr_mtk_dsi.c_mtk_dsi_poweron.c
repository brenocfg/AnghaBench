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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int pixelclock; int hactive; int hback_porch; int hfront_porch; int hsync_len; } ;
struct mtk_dsi {int refcount; int format; int lanes; int /*<<< orphan*/  phy; int /*<<< orphan*/  engine_clk; int /*<<< orphan*/  digital_clk; scalar_t__ panel; int /*<<< orphan*/  data_rate; int /*<<< orphan*/  hs_clk; TYPE_1__ vm; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP_ULL (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int T_HS_EXIT ; 
 int T_HS_PREP ; 
 int T_HS_TRAIL ; 
 int T_HS_ZERO ; 
 int T_LPX ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 scalar_t__ drm_panel_prepare (scalar_t__) ; 
 int /*<<< orphan*/  mtk_dsi_clk_hs_mode (struct mtk_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_dsi_clk_ulp_mode_leave (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_config_vdo_timing (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_enable (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_lane0_ulp_mode_leave (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_phy_timconfig (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_ps_control_vact (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_reset_engine (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_rxtx_control (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_set_interrupt_enable (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_set_vm_cmd (struct mtk_dsi*) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_dsi_poweron(struct mtk_dsi *dsi)
{
	struct device *dev = dsi->dev;
	int ret;
	u64 pixel_clock, total_bits;
	u32 htotal, htotal_bits, bit_per_pixel, overhead_cycles, overhead_bits;

	if (++dsi->refcount != 1)
		return 0;

	switch (dsi->format) {
	case MIPI_DSI_FMT_RGB565:
		bit_per_pixel = 16;
		break;
	case MIPI_DSI_FMT_RGB666_PACKED:
		bit_per_pixel = 18;
		break;
	case MIPI_DSI_FMT_RGB666:
	case MIPI_DSI_FMT_RGB888:
	default:
		bit_per_pixel = 24;
		break;
	}

	/**
	 * htotal_time = htotal * byte_per_pixel / num_lanes
	 * overhead_time = lpx + hs_prepare + hs_zero + hs_trail + hs_exit
	 * mipi_ratio = (htotal_time + overhead_time) / htotal_time
	 * data_rate = pixel_clock * bit_per_pixel * mipi_ratio / num_lanes;
	 */
	pixel_clock = dsi->vm.pixelclock;
	htotal = dsi->vm.hactive + dsi->vm.hback_porch + dsi->vm.hfront_porch +
			dsi->vm.hsync_len;
	htotal_bits = htotal * bit_per_pixel;

	overhead_cycles = T_LPX + T_HS_PREP + T_HS_ZERO + T_HS_TRAIL +
			T_HS_EXIT;
	overhead_bits = overhead_cycles * dsi->lanes * 8;
	total_bits = htotal_bits + overhead_bits;

	dsi->data_rate = DIV_ROUND_UP_ULL(pixel_clock * total_bits,
					  htotal * dsi->lanes);

	ret = clk_set_rate(dsi->hs_clk, dsi->data_rate);
	if (ret < 0) {
		dev_err(dev, "Failed to set data rate: %d\n", ret);
		goto err_refcount;
	}

	phy_power_on(dsi->phy);

	ret = clk_prepare_enable(dsi->engine_clk);
	if (ret < 0) {
		dev_err(dev, "Failed to enable engine clock: %d\n", ret);
		goto err_phy_power_off;
	}

	ret = clk_prepare_enable(dsi->digital_clk);
	if (ret < 0) {
		dev_err(dev, "Failed to enable digital clock: %d\n", ret);
		goto err_disable_engine_clk;
	}

	mtk_dsi_enable(dsi);
	mtk_dsi_reset_engine(dsi);
	mtk_dsi_phy_timconfig(dsi);

	mtk_dsi_rxtx_control(dsi);
	mtk_dsi_ps_control_vact(dsi);
	mtk_dsi_set_vm_cmd(dsi);
	mtk_dsi_config_vdo_timing(dsi);
	mtk_dsi_set_interrupt_enable(dsi);

	mtk_dsi_clk_ulp_mode_leave(dsi);
	mtk_dsi_lane0_ulp_mode_leave(dsi);
	mtk_dsi_clk_hs_mode(dsi, 0);

	if (dsi->panel) {
		if (drm_panel_prepare(dsi->panel)) {
			DRM_ERROR("failed to prepare the panel\n");
			goto err_disable_digital_clk;
		}
	}

	return 0;
err_disable_digital_clk:
	clk_disable_unprepare(dsi->digital_clk);
err_disable_engine_clk:
	clk_disable_unprepare(dsi->engine_clk);
err_phy_power_off:
	phy_power_off(dsi->phy);
err_refcount:
	dsi->refcount--;
	return ret;
}