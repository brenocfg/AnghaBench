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
struct zx_tvenc_mode {int /*<<< orphan*/  phase_line_incr_cvbs; int /*<<< orphan*/  sub_carrier_phase1; int /*<<< orphan*/  control_param; int /*<<< orphan*/  burst_level; int /*<<< orphan*/  blank_black_level; int /*<<< orphan*/  weight_value; int /*<<< orphan*/  line_timing_param; int /*<<< orphan*/  burst_line_even2; int /*<<< orphan*/  burst_line_odd2; int /*<<< orphan*/  burst_line_even1; int /*<<< orphan*/  burst_line_odd1; int /*<<< orphan*/  field2_param; int /*<<< orphan*/  field1_param; int /*<<< orphan*/  video_res; int /*<<< orphan*/  video_info; } ;
struct zx_tvenc {scalar_t__ mmio; int /*<<< orphan*/  dev; } ;
struct vou_div_config {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct vou_div_config*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ VENC_BLANK_BLACK_LEVEL ; 
 scalar_t__ VENC_BURST_LEVEL ; 
 scalar_t__ VENC_CONTROL_PARAM ; 
 scalar_t__ VENC_FIELD1_PARAM ; 
 scalar_t__ VENC_FIELD2_PARAM ; 
 scalar_t__ VENC_LINE_E_1 ; 
 scalar_t__ VENC_LINE_E_2 ; 
 scalar_t__ VENC_LINE_O_1 ; 
 scalar_t__ VENC_LINE_O_2 ; 
 scalar_t__ VENC_LINE_TIMING_PARAM ; 
 scalar_t__ VENC_PHASE_LINE_INCR_CVBS ; 
 scalar_t__ VENC_SUB_CARRIER_PHASE1 ; 
 scalar_t__ VENC_VIDEO_INFO ; 
 scalar_t__ VENC_VIDEO_RES ; 
 scalar_t__ VENC_WEIGHT_VALUE ; 
 int /*<<< orphan*/  VOU_DIV_1 ; 
 int /*<<< orphan*/  VOU_DIV_2 ; 
 int /*<<< orphan*/  VOU_DIV_4 ; 
 int /*<<< orphan*/  VOU_DIV_INF ; 
 int /*<<< orphan*/  VOU_DIV_LAYER ; 
 int /*<<< orphan*/  VOU_DIV_TVENC ; 
 struct zx_tvenc* to_zx_tvenc (struct drm_encoder*) ; 
 struct zx_tvenc_mode* zx_tvenc_find_zmode (struct drm_display_mode*) ; 
 int /*<<< orphan*/  zx_vou_config_dividers (int /*<<< orphan*/ ,struct vou_div_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zx_tvenc_encoder_mode_set(struct drm_encoder *encoder,
				      struct drm_display_mode *mode,
				      struct drm_display_mode *adj_mode)
{
	struct zx_tvenc *tvenc = to_zx_tvenc(encoder);
	const struct zx_tvenc_mode *zmode;
	struct vou_div_config configs[] = {
		{ VOU_DIV_INF,   VOU_DIV_4 },
		{ VOU_DIV_TVENC, VOU_DIV_1 },
		{ VOU_DIV_LAYER, VOU_DIV_2 },
	};

	zx_vou_config_dividers(encoder->crtc, configs, ARRAY_SIZE(configs));

	zmode = zx_tvenc_find_zmode(mode);
	if (!zmode) {
		DRM_DEV_ERROR(tvenc->dev, "failed to find zmode\n");
		return;
	}

	zx_writel(tvenc->mmio + VENC_VIDEO_INFO, zmode->video_info);
	zx_writel(tvenc->mmio + VENC_VIDEO_RES, zmode->video_res);
	zx_writel(tvenc->mmio + VENC_FIELD1_PARAM, zmode->field1_param);
	zx_writel(tvenc->mmio + VENC_FIELD2_PARAM, zmode->field2_param);
	zx_writel(tvenc->mmio + VENC_LINE_O_1, zmode->burst_line_odd1);
	zx_writel(tvenc->mmio + VENC_LINE_E_1, zmode->burst_line_even1);
	zx_writel(tvenc->mmio + VENC_LINE_O_2, zmode->burst_line_odd2);
	zx_writel(tvenc->mmio + VENC_LINE_E_2, zmode->burst_line_even2);
	zx_writel(tvenc->mmio + VENC_LINE_TIMING_PARAM,
		  zmode->line_timing_param);
	zx_writel(tvenc->mmio + VENC_WEIGHT_VALUE, zmode->weight_value);
	zx_writel(tvenc->mmio + VENC_BLANK_BLACK_LEVEL,
		  zmode->blank_black_level);
	zx_writel(tvenc->mmio + VENC_BURST_LEVEL, zmode->burst_level);
	zx_writel(tvenc->mmio + VENC_CONTROL_PARAM, zmode->control_param);
	zx_writel(tvenc->mmio + VENC_SUB_CARRIER_PHASE1,
		  zmode->sub_carrier_phase1);
	zx_writel(tvenc->mmio + VENC_PHASE_LINE_INCR_CVBS,
		  zmode->phase_line_incr_cvbs);
}