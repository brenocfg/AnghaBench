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
typedef  int u32 ;
struct intf_timing_params {int hsync_pulse_width; int h_back_porch; int width; int h_front_porch; int vsync_pulse_width; int v_back_porch; int height; int v_front_porch; int hsync_skew; scalar_t__ xres; int yres; int border_clr; int underflow_clr; } ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_intf {TYPE_1__* cap; struct dpu_hw_blk_reg_map hw; } ;
struct dpu_format {int* bits; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int BIT (int) ; 
 size_t C0_G_Y ; 
 size_t C1_B_Cb ; 
 size_t C2_R_Cr ; 
 int COLOR_8BIT ; 
 int /*<<< orphan*/  DPU_FORMAT_IS_YUV (struct dpu_format const*) ; 
 int DPU_REG_READ (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INTF_ACTIVE_HCTL ; 
 int /*<<< orphan*/  INTF_ACTIVE_V_END_F0 ; 
 int /*<<< orphan*/  INTF_ACTIVE_V_START_F0 ; 
 int /*<<< orphan*/  INTF_BORDER_COLOR ; 
 int /*<<< orphan*/  INTF_CONFIG ; 
 int /*<<< orphan*/  INTF_DISPLAY_HCTL ; 
 int /*<<< orphan*/  INTF_DISPLAY_V_END_F0 ; 
 int /*<<< orphan*/  INTF_DISPLAY_V_START_F0 ; 
 scalar_t__ INTF_DP ; 
 scalar_t__ INTF_EDP ; 
 int /*<<< orphan*/  INTF_FRAME_LINE_COUNT_EN ; 
 scalar_t__ INTF_HDMI ; 
 int /*<<< orphan*/  INTF_HSYNC_CTL ; 
 int /*<<< orphan*/  INTF_HSYNC_SKEW ; 
 int /*<<< orphan*/  INTF_PANEL_FORMAT ; 
 int /*<<< orphan*/  INTF_POLARITY_CTL ; 
 int /*<<< orphan*/  INTF_UNDERFLOW_COLOR ; 
 int /*<<< orphan*/  INTF_VSYNC_PERIOD_F0 ; 
 int /*<<< orphan*/  INTF_VSYNC_PULSE_WIDTH_F0 ; 

__attribute__((used)) static void dpu_hw_intf_setup_timing_engine(struct dpu_hw_intf *ctx,
		const struct intf_timing_params *p,
		const struct dpu_format *fmt)
{
	struct dpu_hw_blk_reg_map *c = &ctx->hw;
	u32 hsync_period, vsync_period;
	u32 display_v_start, display_v_end;
	u32 hsync_start_x, hsync_end_x;
	u32 active_h_start, active_h_end;
	u32 active_v_start, active_v_end;
	u32 active_hctl, display_hctl, hsync_ctl;
	u32 polarity_ctl, den_polarity, hsync_polarity, vsync_polarity;
	u32 panel_format;
	u32 intf_cfg;

	/* read interface_cfg */
	intf_cfg = DPU_REG_READ(c, INTF_CONFIG);
	hsync_period = p->hsync_pulse_width + p->h_back_porch + p->width +
	p->h_front_porch;
	vsync_period = p->vsync_pulse_width + p->v_back_porch + p->height +
	p->v_front_porch;

	display_v_start = ((p->vsync_pulse_width + p->v_back_porch) *
	hsync_period) + p->hsync_skew;
	display_v_end = ((vsync_period - p->v_front_porch) * hsync_period) +
	p->hsync_skew - 1;

	if (ctx->cap->type == INTF_EDP || ctx->cap->type == INTF_DP) {
		display_v_start += p->hsync_pulse_width + p->h_back_porch;
		display_v_end -= p->h_front_porch;
	}

	hsync_start_x = p->h_back_porch + p->hsync_pulse_width;
	hsync_end_x = hsync_period - p->h_front_porch - 1;

	if (p->width != p->xres) {
		active_h_start = hsync_start_x;
		active_h_end = active_h_start + p->xres - 1;
	} else {
		active_h_start = 0;
		active_h_end = 0;
	}

	if (p->height != p->yres) {
		active_v_start = display_v_start;
		active_v_end = active_v_start + (p->yres * hsync_period) - 1;
	} else {
		active_v_start = 0;
		active_v_end = 0;
	}

	if (active_h_end) {
		active_hctl = (active_h_end << 16) | active_h_start;
		intf_cfg |= BIT(29);	/* ACTIVE_H_ENABLE */
	} else {
		active_hctl = 0;
	}

	if (active_v_end)
		intf_cfg |= BIT(30); /* ACTIVE_V_ENABLE */

	hsync_ctl = (hsync_period << 16) | p->hsync_pulse_width;
	display_hctl = (hsync_end_x << 16) | hsync_start_x;

	den_polarity = 0;
	if (ctx->cap->type == INTF_HDMI) {
		hsync_polarity = p->yres >= 720 ? 0 : 1;
		vsync_polarity = p->yres >= 720 ? 0 : 1;
	} else {
		hsync_polarity = 0;
		vsync_polarity = 0;
	}
	polarity_ctl = (den_polarity << 2) | /*  DEN Polarity  */
		(vsync_polarity << 1) | /* VSYNC Polarity */
		(hsync_polarity << 0);  /* HSYNC Polarity */

	if (!DPU_FORMAT_IS_YUV(fmt))
		panel_format = (fmt->bits[C0_G_Y] |
				(fmt->bits[C1_B_Cb] << 2) |
				(fmt->bits[C2_R_Cr] << 4) |
				(0x21 << 8));
	else
		/* Interface treats all the pixel data in RGB888 format */
		panel_format = (COLOR_8BIT |
				(COLOR_8BIT << 2) |
				(COLOR_8BIT << 4) |
				(0x21 << 8));

	DPU_REG_WRITE(c, INTF_HSYNC_CTL, hsync_ctl);
	DPU_REG_WRITE(c, INTF_VSYNC_PERIOD_F0, vsync_period * hsync_period);
	DPU_REG_WRITE(c, INTF_VSYNC_PULSE_WIDTH_F0,
			p->vsync_pulse_width * hsync_period);
	DPU_REG_WRITE(c, INTF_DISPLAY_HCTL, display_hctl);
	DPU_REG_WRITE(c, INTF_DISPLAY_V_START_F0, display_v_start);
	DPU_REG_WRITE(c, INTF_DISPLAY_V_END_F0, display_v_end);
	DPU_REG_WRITE(c, INTF_ACTIVE_HCTL,  active_hctl);
	DPU_REG_WRITE(c, INTF_ACTIVE_V_START_F0, active_v_start);
	DPU_REG_WRITE(c, INTF_ACTIVE_V_END_F0, active_v_end);
	DPU_REG_WRITE(c, INTF_BORDER_COLOR, p->border_clr);
	DPU_REG_WRITE(c, INTF_UNDERFLOW_COLOR, p->underflow_clr);
	DPU_REG_WRITE(c, INTF_HSYNC_SKEW, p->hsync_skew);
	DPU_REG_WRITE(c, INTF_POLARITY_CTL, polarity_ctl);
	DPU_REG_WRITE(c, INTF_FRAME_LINE_COUNT_EN, 0x3);
	DPU_REG_WRITE(c, INTF_CONFIG, intf_cfg);
	DPU_REG_WRITE(c, INTF_PANEL_FORMAT, panel_format);
}