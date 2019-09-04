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
typedef  int u32 ;
struct mdfld_dsi_dpi_timing {int hsync_count; int hbp_count; int hfp_count; int hactive_count; int vsync_count; int vbp_count; int vfp_count; } ;
struct mdfld_dsi_config {int lane_count; int channel_num; int bpp; int video_mode; struct drm_display_mode* mode; struct drm_device* dev; } ;
struct drm_display_mode {int vtotal; int htotal; int vdisplay; int hdisplay; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int DSI_DPI_COLOR_FORMAT_RGB565 ; 
 int DSI_DPI_COLOR_FORMAT_RGB666 ; 
 int DSI_DPI_COLOR_FORMAT_RGB888 ; 
 int DSI_DPI_COMPLETE_LAST_LINE ; 
 int DSI_DPI_TIMING_MASK ; 
 int DSI_DPI_VIRT_CHANNEL_OFFSET ; 
 int DSI_HS_TX_TIMEOUT_MASK ; 
 int DSI_LP_RX_TIMEOUT_MASK ; 
 int DSI_RESET_TIMER_MASK ; 
 int DSI_TURN_AROUND_TIMEOUT_MASK ; 
 int /*<<< orphan*/  MIPI_CLK_LANE_SWITCH_TIME_CNT_REG (int) ; 
 int /*<<< orphan*/  MIPI_CTRL_REG (int) ; 
 int /*<<< orphan*/  MIPI_DEVICE_READY_REG (int) ; 
 int /*<<< orphan*/  MIPI_DEVICE_RESET_TIMER_REG (int) ; 
 int /*<<< orphan*/  MIPI_DPHY_PARAM_REG (int) ; 
 int /*<<< orphan*/  MIPI_DPI_RESOLUTION_REG (int) ; 
 int /*<<< orphan*/  MIPI_DSI_FUNC_PRG_REG (int) ; 
 int /*<<< orphan*/  MIPI_EOT_DISABLE_REG (int) ; 
 int /*<<< orphan*/  MIPI_HACTIVE_COUNT_REG (int) ; 
 int /*<<< orphan*/  MIPI_HBP_COUNT_REG (int) ; 
 int /*<<< orphan*/  MIPI_HFP_COUNT_REG (int) ; 
 int /*<<< orphan*/  MIPI_HIGH_LOW_SWITCH_COUNT_REG (int) ; 
 int /*<<< orphan*/  MIPI_HSYNC_COUNT_REG (int) ; 
 int /*<<< orphan*/  MIPI_HS_TX_TIMEOUT_REG (int) ; 
 int /*<<< orphan*/  MIPI_INIT_COUNT_REG (int) ; 
 int /*<<< orphan*/  MIPI_INTR_EN_REG (int) ; 
 int /*<<< orphan*/  MIPI_LP_BYTECLK_REG (int) ; 
 int /*<<< orphan*/  MIPI_LP_RX_TIMEOUT_REG (int) ; 
 int /*<<< orphan*/  MIPI_TURN_AROUND_TIMEOUT_REG (int) ; 
 int /*<<< orphan*/  MIPI_VBP_COUNT_REG (int) ; 
 int /*<<< orphan*/  MIPI_VFP_COUNT_REG (int) ; 
 int /*<<< orphan*/  MIPI_VIDEO_MODE_FORMAT_REG (int) ; 
 int /*<<< orphan*/  MIPI_VSYNC_COUNT_REG (int) ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TC35876X ; 
 int /*<<< orphan*/  mdfld_dsi_dpi_timing_calculation (struct drm_display_mode*,struct mdfld_dsi_dpi_timing*,int,int) ; 
 scalar_t__ mdfld_get_panel_type (struct drm_device*,int) ; 
 int /*<<< orphan*/  tc35876x_set_bridge_reset_state (struct drm_device*,int /*<<< orphan*/ ) ; 

void mdfld_dsi_dpi_controller_init(struct mdfld_dsi_config *dsi_config,
								int pipe)
{
	struct drm_device *dev = dsi_config->dev;
	int lane_count = dsi_config->lane_count;
	struct mdfld_dsi_dpi_timing dpi_timing;
	struct drm_display_mode *mode = dsi_config->mode;
	u32 val;

	/*un-ready device*/
	REG_FLD_MOD(MIPI_DEVICE_READY_REG(pipe), 0, 0, 0);

	/*init dsi adapter before kicking off*/
	REG_WRITE(MIPI_CTRL_REG(pipe), 0x00000018);

	/*enable all interrupts*/
	REG_WRITE(MIPI_INTR_EN_REG(pipe), 0xffffffff);

	/*set up func_prg*/
	val = lane_count;
	val |= dsi_config->channel_num << DSI_DPI_VIRT_CHANNEL_OFFSET;

	switch (dsi_config->bpp) {
	case 16:
		val |= DSI_DPI_COLOR_FORMAT_RGB565;
		break;
	case 18:
		val |= DSI_DPI_COLOR_FORMAT_RGB666;
		break;
	case 24:
		val |= DSI_DPI_COLOR_FORMAT_RGB888;
		break;
	default:
		DRM_ERROR("unsupported color format, bpp = %d\n",
							dsi_config->bpp);
	}
	REG_WRITE(MIPI_DSI_FUNC_PRG_REG(pipe), val);

	REG_WRITE(MIPI_HS_TX_TIMEOUT_REG(pipe),
			(mode->vtotal * mode->htotal * dsi_config->bpp /
				(8 * lane_count)) & DSI_HS_TX_TIMEOUT_MASK);
	REG_WRITE(MIPI_LP_RX_TIMEOUT_REG(pipe),
				0xffff & DSI_LP_RX_TIMEOUT_MASK);

	/*max value: 20 clock cycles of txclkesc*/
	REG_WRITE(MIPI_TURN_AROUND_TIMEOUT_REG(pipe),
				0x14 & DSI_TURN_AROUND_TIMEOUT_MASK);

	/*min 21 txclkesc, max: ffffh*/
	REG_WRITE(MIPI_DEVICE_RESET_TIMER_REG(pipe),
				0xffff & DSI_RESET_TIMER_MASK);

	REG_WRITE(MIPI_DPI_RESOLUTION_REG(pipe),
				mode->vdisplay << 16 | mode->hdisplay);

	/*set DPI timing registers*/
	mdfld_dsi_dpi_timing_calculation(mode, &dpi_timing,
				dsi_config->lane_count, dsi_config->bpp);

	REG_WRITE(MIPI_HSYNC_COUNT_REG(pipe),
			dpi_timing.hsync_count & DSI_DPI_TIMING_MASK);
	REG_WRITE(MIPI_HBP_COUNT_REG(pipe),
			dpi_timing.hbp_count & DSI_DPI_TIMING_MASK);
	REG_WRITE(MIPI_HFP_COUNT_REG(pipe),
			dpi_timing.hfp_count & DSI_DPI_TIMING_MASK);
	REG_WRITE(MIPI_HACTIVE_COUNT_REG(pipe),
			dpi_timing.hactive_count & DSI_DPI_TIMING_MASK);
	REG_WRITE(MIPI_VSYNC_COUNT_REG(pipe),
			dpi_timing.vsync_count & DSI_DPI_TIMING_MASK);
	REG_WRITE(MIPI_VBP_COUNT_REG(pipe),
			dpi_timing.vbp_count & DSI_DPI_TIMING_MASK);
	REG_WRITE(MIPI_VFP_COUNT_REG(pipe),
			dpi_timing.vfp_count & DSI_DPI_TIMING_MASK);

	REG_WRITE(MIPI_HIGH_LOW_SWITCH_COUNT_REG(pipe), 0x46);

	/*min: 7d0 max: 4e20*/
	REG_WRITE(MIPI_INIT_COUNT_REG(pipe), 0x000007d0);

	/*set up video mode*/
	val = dsi_config->video_mode | DSI_DPI_COMPLETE_LAST_LINE;
	REG_WRITE(MIPI_VIDEO_MODE_FORMAT_REG(pipe), val);

	REG_WRITE(MIPI_EOT_DISABLE_REG(pipe), 0x00000000);

	REG_WRITE(MIPI_LP_BYTECLK_REG(pipe), 0x00000004);

	/*TODO: figure out how to setup these registers*/
	if (mdfld_get_panel_type(dev, pipe) == TC35876X)
		REG_WRITE(MIPI_DPHY_PARAM_REG(pipe), 0x2A0c6008);
	else
		REG_WRITE(MIPI_DPHY_PARAM_REG(pipe), 0x150c3408);

	REG_WRITE(MIPI_CLK_LANE_SWITCH_TIME_CNT_REG(pipe), (0xa << 16) | 0x14);

	if (mdfld_get_panel_type(dev, pipe) == TC35876X)
		tc35876x_set_bridge_reset_state(dev, 0);  /*Pull High Reset */

	/*set device ready*/
	REG_FLD_MOD(MIPI_DEVICE_READY_REG(pipe), 1, 0, 0);
}