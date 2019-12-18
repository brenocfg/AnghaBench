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
typedef  int u8 ;
typedef  int u32 ;
struct ipu_plane_state {scalar_t__ use_pre; } ;
struct TYPE_6__ {TYPE_1__* dev; } ;
struct ipu_plane {int dp_flow; int /*<<< orphan*/  ipu_ch; TYPE_2__ base; int /*<<< orphan*/  alpha_ch; int /*<<< orphan*/  dmfc; int /*<<< orphan*/  dp; int /*<<< orphan*/  dma; } ;
struct drm_rect {int x1; int y1; } ;
struct drm_plane_state {int normalized_zpos; struct drm_rect src; struct drm_framebuffer* fb; struct drm_rect dst; TYPE_3__* crtc; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_framebuffer {int /*<<< orphan*/ * pitches; TYPE_4__* format; int /*<<< orphan*/  modifier; } ;
struct drm_format_info {int /*<<< orphan*/ * cpp; } ;
struct drm_crtc_state {int dummy; } ;
typedef  enum ipu_color_space { ____Placeholder_ipu_color_space } ipu_color_space ;
struct TYPE_8__ {int const format; int /*<<< orphan*/  has_alpha; } ;
struct TYPE_7__ {struct drm_crtc_state* state; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DRM_FORMAT_BGR565_A8 143 
#define  DRM_FORMAT_BGR888_A8 142 
#define  DRM_FORMAT_BGRX8888_A8 141 
#define  DRM_FORMAT_NV12 140 
#define  DRM_FORMAT_NV16 139 
#define  DRM_FORMAT_RGB565_A8 138 
#define  DRM_FORMAT_RGB888_A8 137 
#define  DRM_FORMAT_RGBX8888_A8 136 
#define  DRM_FORMAT_YUV420 135 
#define  DRM_FORMAT_YUV422 134 
#define  DRM_FORMAT_YUV444 133 
#define  DRM_FORMAT_YVU420 132 
#define  DRM_FORMAT_YVU422 131 
#define  DRM_FORMAT_YVU444 130 
 int /*<<< orphan*/  IPUV3_COLORSPACE_RGB ; 
 int /*<<< orphan*/  IPUV3_COLORSPACE_UNKNOWN ; 
#define  IPU_DP_FLOW_SYNC_BG 129 
#define  IPU_DP_FLOW_SYNC_FG 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,int,int,...) ; 
 int /*<<< orphan*/  drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 
 struct drm_format_info* drm_format_info (int) ; 
 unsigned long drm_plane_state_to_eba (struct drm_plane_state*,int) ; 
 unsigned long drm_plane_state_to_ubo (struct drm_plane_state*) ; 
 unsigned long drm_plane_state_to_vbo (struct drm_plane_state*) ; 
 int drm_rect_height (struct drm_rect*) ; 
 int drm_rect_width (struct drm_rect*) ; 
 int /*<<< orphan*/  ipu_calculate_bursts (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 unsigned int ipu_chan_assign_axi_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cpmem_set_axi_id (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ipu_cpmem_set_buffer (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  ipu_cpmem_set_burstsize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_cpmem_set_fmt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_cpmem_set_format_passthrough (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_cpmem_set_high_priority (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cpmem_set_resolution (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ipu_cpmem_set_stride (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cpmem_set_yuv_planar_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ipu_cpmem_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dmfc_config_wait4eot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_dp_set_global_alpha (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ipu_dp_set_window_pos (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ipu_dp_setup_channel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ipu_drm_fourcc_to_colorspace (int const) ; 
 int /*<<< orphan*/  ipu_idmac_enable_watermark (int /*<<< orphan*/ ,int) ; 
 int ipu_idmac_get_current_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_lock_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_idmac_select_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_idmac_set_double_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_plane_enable (struct ipu_plane*) ; 
 scalar_t__ ipu_plane_separate_alpha (struct ipu_plane*) ; 
 int /*<<< orphan*/  ipu_prg_channel_configure (int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  swap (unsigned long,unsigned long) ; 
 struct ipu_plane* to_ipu_plane (struct drm_plane*) ; 
 struct ipu_plane_state* to_ipu_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static void ipu_plane_atomic_update(struct drm_plane *plane,
				    struct drm_plane_state *old_state)
{
	struct ipu_plane *ipu_plane = to_ipu_plane(plane);
	struct drm_plane_state *state = plane->state;
	struct ipu_plane_state *ipu_state = to_ipu_plane_state(state);
	struct drm_crtc_state *crtc_state = state->crtc->state;
	struct drm_framebuffer *fb = state->fb;
	struct drm_rect *dst = &state->dst;
	unsigned long eba, ubo, vbo;
	unsigned long alpha_eba = 0;
	enum ipu_color_space ics;
	unsigned int axi_id = 0;
	const struct drm_format_info *info;
	u8 burstsize, num_bursts;
	u32 width, height;
	int active;

	if (ipu_plane->dp_flow == IPU_DP_FLOW_SYNC_FG)
		ipu_dp_set_window_pos(ipu_plane->dp, dst->x1, dst->y1);

	switch (ipu_plane->dp_flow) {
	case IPU_DP_FLOW_SYNC_BG:
		if (state->normalized_zpos == 1) {
			ipu_dp_set_global_alpha(ipu_plane->dp,
						!fb->format->has_alpha, 0xff,
						true);
		} else {
			ipu_dp_set_global_alpha(ipu_plane->dp, true, 0, true);
		}
		break;
	case IPU_DP_FLOW_SYNC_FG:
		if (state->normalized_zpos == 1) {
			ipu_dp_set_global_alpha(ipu_plane->dp,
						!fb->format->has_alpha, 0xff,
						false);
		}
		break;
	}

	eba = drm_plane_state_to_eba(state, 0);

	/*
	 * Configure PRG channel and attached PRE, this changes the EBA to an
	 * internal SRAM location.
	 */
	if (ipu_state->use_pre) {
		axi_id = ipu_chan_assign_axi_id(ipu_plane->dma);
		ipu_prg_channel_configure(ipu_plane->ipu_ch, axi_id,
					  drm_rect_width(&state->src) >> 16,
					  drm_rect_height(&state->src) >> 16,
					  fb->pitches[0], fb->format->format,
					  fb->modifier, &eba);
	}

	if (old_state->fb && !drm_atomic_crtc_needs_modeset(crtc_state)) {
		/* nothing to do if PRE is used */
		if (ipu_state->use_pre)
			return;
		active = ipu_idmac_get_current_buffer(ipu_plane->ipu_ch);
		ipu_cpmem_set_buffer(ipu_plane->ipu_ch, !active, eba);
		ipu_idmac_select_buffer(ipu_plane->ipu_ch, !active);
		if (ipu_plane_separate_alpha(ipu_plane)) {
			active = ipu_idmac_get_current_buffer(ipu_plane->alpha_ch);
			ipu_cpmem_set_buffer(ipu_plane->alpha_ch, !active,
					     alpha_eba);
			ipu_idmac_select_buffer(ipu_plane->alpha_ch, !active);
		}
		return;
	}

	ics = ipu_drm_fourcc_to_colorspace(fb->format->format);
	switch (ipu_plane->dp_flow) {
	case IPU_DP_FLOW_SYNC_BG:
		ipu_dp_setup_channel(ipu_plane->dp, ics, IPUV3_COLORSPACE_RGB);
		break;
	case IPU_DP_FLOW_SYNC_FG:
		ipu_dp_setup_channel(ipu_plane->dp, ics,
					IPUV3_COLORSPACE_UNKNOWN);
		break;
	}

	ipu_dmfc_config_wait4eot(ipu_plane->dmfc, drm_rect_width(dst));

	width = drm_rect_width(&state->src) >> 16;
	height = drm_rect_height(&state->src) >> 16;
	info = drm_format_info(fb->format->format);
	ipu_calculate_bursts(width, info->cpp[0], fb->pitches[0],
			     &burstsize, &num_bursts);

	ipu_cpmem_zero(ipu_plane->ipu_ch);
	ipu_cpmem_set_resolution(ipu_plane->ipu_ch, width, height);
	ipu_cpmem_set_fmt(ipu_plane->ipu_ch, fb->format->format);
	ipu_cpmem_set_burstsize(ipu_plane->ipu_ch, burstsize);
	ipu_cpmem_set_high_priority(ipu_plane->ipu_ch);
	ipu_idmac_enable_watermark(ipu_plane->ipu_ch, true);
	ipu_idmac_set_double_buffer(ipu_plane->ipu_ch, 1);
	ipu_cpmem_set_stride(ipu_plane->ipu_ch, fb->pitches[0]);
	ipu_cpmem_set_axi_id(ipu_plane->ipu_ch, axi_id);

	switch (fb->format->format) {
	case DRM_FORMAT_YUV420:
	case DRM_FORMAT_YVU420:
	case DRM_FORMAT_YUV422:
	case DRM_FORMAT_YVU422:
	case DRM_FORMAT_YUV444:
	case DRM_FORMAT_YVU444:
		ubo = drm_plane_state_to_ubo(state);
		vbo = drm_plane_state_to_vbo(state);
		if (fb->format->format == DRM_FORMAT_YVU420 ||
		    fb->format->format == DRM_FORMAT_YVU422 ||
		    fb->format->format == DRM_FORMAT_YVU444)
			swap(ubo, vbo);

		ipu_cpmem_set_yuv_planar_full(ipu_plane->ipu_ch,
					      fb->pitches[1], ubo, vbo);

		dev_dbg(ipu_plane->base.dev->dev,
			"phy = %lu %lu %lu, x = %d, y = %d", eba, ubo, vbo,
			state->src.x1 >> 16, state->src.y1 >> 16);
		break;
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_NV16:
		ubo = drm_plane_state_to_ubo(state);

		ipu_cpmem_set_yuv_planar_full(ipu_plane->ipu_ch,
					      fb->pitches[1], ubo, ubo);

		dev_dbg(ipu_plane->base.dev->dev,
			"phy = %lu %lu, x = %d, y = %d", eba, ubo,
			state->src.x1 >> 16, state->src.y1 >> 16);
		break;
	case DRM_FORMAT_RGB565_A8:
	case DRM_FORMAT_BGR565_A8:
	case DRM_FORMAT_RGB888_A8:
	case DRM_FORMAT_BGR888_A8:
	case DRM_FORMAT_RGBX8888_A8:
	case DRM_FORMAT_BGRX8888_A8:
		alpha_eba = drm_plane_state_to_eba(state, 1);
		num_bursts = 0;

		dev_dbg(ipu_plane->base.dev->dev, "phys = %lu %lu, x = %d, y = %d",
			eba, alpha_eba, state->src.x1 >> 16, state->src.y1 >> 16);

		ipu_cpmem_set_burstsize(ipu_plane->ipu_ch, 16);

		ipu_cpmem_zero(ipu_plane->alpha_ch);
		ipu_cpmem_set_resolution(ipu_plane->alpha_ch,
					 drm_rect_width(&state->src) >> 16,
					 drm_rect_height(&state->src) >> 16);
		ipu_cpmem_set_format_passthrough(ipu_plane->alpha_ch, 8);
		ipu_cpmem_set_high_priority(ipu_plane->alpha_ch);
		ipu_idmac_set_double_buffer(ipu_plane->alpha_ch, 1);
		ipu_cpmem_set_stride(ipu_plane->alpha_ch, fb->pitches[1]);
		ipu_cpmem_set_burstsize(ipu_plane->alpha_ch, 16);
		ipu_cpmem_set_buffer(ipu_plane->alpha_ch, 0, alpha_eba);
		ipu_cpmem_set_buffer(ipu_plane->alpha_ch, 1, alpha_eba);
		break;
	default:
		dev_dbg(ipu_plane->base.dev->dev, "phys = %lu, x = %d, y = %d",
			eba, state->src.x1 >> 16, state->src.y1 >> 16);
		break;
	}
	ipu_cpmem_set_buffer(ipu_plane->ipu_ch, 0, eba);
	ipu_cpmem_set_buffer(ipu_plane->ipu_ch, 1, eba);
	ipu_idmac_lock_enable(ipu_plane->ipu_ch, num_bursts);
	ipu_plane_enable(ipu_plane);
}