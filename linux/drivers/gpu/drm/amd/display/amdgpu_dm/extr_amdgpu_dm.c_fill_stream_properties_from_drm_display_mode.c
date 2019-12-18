#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_display_mode {int flags; int crtc_clock; scalar_t__ crtc_vsync_start; scalar_t__ crtc_vsync_end; scalar_t__ crtc_vdisplay; int /*<<< orphan*/  crtc_vtotal; scalar_t__ crtc_hdisplay; scalar_t__ crtc_hsync_start; scalar_t__ crtc_hsync_end; int /*<<< orphan*/  crtc_htotal; } ;
struct drm_display_info {int color_formats; } ;
struct drm_connector_state {int dummy; } ;
struct drm_connector {struct drm_display_info display_info; } ;
struct TYPE_3__ {int HSYNC_POSITIVE_POLARITY; int VSYNC_POSITIVE_POLARITY; } ;
struct dc_crtc_timing {int pix_clk_100hz; int /*<<< orphan*/  aspect_ratio; scalar_t__ v_sync_width; scalar_t__ v_front_porch; scalar_t__ v_addressable; int /*<<< orphan*/  v_total; scalar_t__ h_front_porch; scalar_t__ h_sync_width; int /*<<< orphan*/  h_total; scalar_t__ h_addressable; TYPE_1__ flags; int /*<<< orphan*/  vic; scalar_t__ hdmi_vic; int /*<<< orphan*/  scan_type; int /*<<< orphan*/  display_color_depth; int /*<<< orphan*/  timing_3d_format; int /*<<< orphan*/  pixel_encoding; scalar_t__ v_border_bottom; scalar_t__ v_border_top; scalar_t__ h_border_right; scalar_t__ h_border_left; } ;
struct dc_stream_state {scalar_t__ signal; TYPE_2__* out_transfer_func; int /*<<< orphan*/  output_color_space; struct dc_crtc_timing timing; } ;
struct TYPE_4__ {int /*<<< orphan*/  tf; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int DRM_COLOR_FORMAT_YCRCB444 ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  PIXEL_ENCODING_RGB ; 
 int /*<<< orphan*/  PIXEL_ENCODING_YCBCR420 ; 
 int /*<<< orphan*/  PIXEL_ENCODING_YCBCR444 ; 
 int /*<<< orphan*/  SCANNING_TYPE_NODATA ; 
 scalar_t__ SIGNAL_TYPE_HDMI_TYPE_A ; 
 int /*<<< orphan*/  TF_TYPE_PREDEFINED ; 
 int /*<<< orphan*/  TIMING_3D_FORMAT_NONE ; 
 int /*<<< orphan*/  TRANSFER_FUNCTION_SRGB ; 
 int /*<<< orphan*/  adjust_colour_depth_from_display_info (struct dc_crtc_timing*,struct drm_display_info const*) ; 
 int /*<<< orphan*/  convert_color_depth_from_display_info (struct drm_connector const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  drm_match_cea_mode (struct drm_display_mode const*) ; 
 scalar_t__ drm_mode_is_420_only (struct drm_display_info const*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  get_aspect_ratio (struct drm_display_mode const*) ; 
 int /*<<< orphan*/  get_output_color_space (struct dc_crtc_timing*) ; 
 int /*<<< orphan*/  memset (struct dc_crtc_timing*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_stream_properties_from_drm_display_mode(
	struct dc_stream_state *stream,
	const struct drm_display_mode *mode_in,
	const struct drm_connector *connector,
	const struct drm_connector_state *connector_state,
	const struct dc_stream_state *old_stream)
{
	struct dc_crtc_timing *timing_out = &stream->timing;
	const struct drm_display_info *info = &connector->display_info;

	memset(timing_out, 0, sizeof(struct dc_crtc_timing));

	timing_out->h_border_left = 0;
	timing_out->h_border_right = 0;
	timing_out->v_border_top = 0;
	timing_out->v_border_bottom = 0;
	/* TODO: un-hardcode */
	if (drm_mode_is_420_only(info, mode_in)
			&& stream->signal == SIGNAL_TYPE_HDMI_TYPE_A)
		timing_out->pixel_encoding = PIXEL_ENCODING_YCBCR420;
	else if ((connector->display_info.color_formats & DRM_COLOR_FORMAT_YCRCB444)
			&& stream->signal == SIGNAL_TYPE_HDMI_TYPE_A)
		timing_out->pixel_encoding = PIXEL_ENCODING_YCBCR444;
	else
		timing_out->pixel_encoding = PIXEL_ENCODING_RGB;

	timing_out->timing_3d_format = TIMING_3D_FORMAT_NONE;
	timing_out->display_color_depth = convert_color_depth_from_display_info(
		connector, connector_state);
	timing_out->scan_type = SCANNING_TYPE_NODATA;
	timing_out->hdmi_vic = 0;

	if(old_stream) {
		timing_out->vic = old_stream->timing.vic;
		timing_out->flags.HSYNC_POSITIVE_POLARITY = old_stream->timing.flags.HSYNC_POSITIVE_POLARITY;
		timing_out->flags.VSYNC_POSITIVE_POLARITY = old_stream->timing.flags.VSYNC_POSITIVE_POLARITY;
	} else {
		timing_out->vic = drm_match_cea_mode(mode_in);
		if (mode_in->flags & DRM_MODE_FLAG_PHSYNC)
			timing_out->flags.HSYNC_POSITIVE_POLARITY = 1;
		if (mode_in->flags & DRM_MODE_FLAG_PVSYNC)
			timing_out->flags.VSYNC_POSITIVE_POLARITY = 1;
	}

	timing_out->h_addressable = mode_in->crtc_hdisplay;
	timing_out->h_total = mode_in->crtc_htotal;
	timing_out->h_sync_width =
		mode_in->crtc_hsync_end - mode_in->crtc_hsync_start;
	timing_out->h_front_porch =
		mode_in->crtc_hsync_start - mode_in->crtc_hdisplay;
	timing_out->v_total = mode_in->crtc_vtotal;
	timing_out->v_addressable = mode_in->crtc_vdisplay;
	timing_out->v_front_porch =
		mode_in->crtc_vsync_start - mode_in->crtc_vdisplay;
	timing_out->v_sync_width =
		mode_in->crtc_vsync_end - mode_in->crtc_vsync_start;
	timing_out->pix_clk_100hz = mode_in->crtc_clock * 10;
	timing_out->aspect_ratio = get_aspect_ratio(mode_in);

	stream->output_color_space = get_output_color_space(timing_out);

	stream->out_transfer_func->type = TF_TYPE_PREDEFINED;
	stream->out_transfer_func->tf = TRANSFER_FUNCTION_SRGB;
	if (stream->signal == SIGNAL_TYPE_HDMI_TYPE_A)
		adjust_colour_depth_from_display_info(timing_out, info);
}