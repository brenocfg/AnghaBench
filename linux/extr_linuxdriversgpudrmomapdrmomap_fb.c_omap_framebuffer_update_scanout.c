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
typedef  int u32 ;
struct plane {int dummy; } ;
struct omap_overlay_info {int width; int height; scalar_t__ rotation_type; int rotation; void* p_uv_addr; int /*<<< orphan*/  screen_width; void* paddr; int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; int /*<<< orphan*/  fourcc; } ;
struct omap_framebuffer {struct plane* planes; struct drm_format_info* format; } ;
struct drm_plane_state {int src_w; int src_h; int rotation; int src_x; int src_y; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; } ;
struct drm_framebuffer {int /*<<< orphan*/ * obj; TYPE_2__* format; int /*<<< orphan*/ * pitches; TYPE_1__* dev; } ;
struct drm_format_info {int /*<<< orphan*/ * cpp; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_FORMAT_NV12 ; 
 int /*<<< orphan*/  DRM_FORMAT_UYVY ; 
 int /*<<< orphan*/  DRM_FORMAT_YUYV ; 
#define  DRM_MODE_ROTATE_0 128 
 int DRM_MODE_ROTATE_MASK ; 
 int MASK_X_INVERT ; 
 int MASK_Y_INVERT ; 
 int OMAP_BO_TILED ; 
 scalar_t__ OMAP_DSS_ROT_NONE ; 
 scalar_t__ OMAP_DSS_ROT_TILER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ drm_rotation_90_or_270 (int) ; 
 int drm_rotation_to_tiler (int) ; 
 void* get_linear_addr (struct drm_framebuffer*,struct drm_format_info const*,int,int,int) ; 
 int omap_gem_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_gem_rotated_dma_addr (int /*<<< orphan*/ ,int,int,int,void**) ; 
 int /*<<< orphan*/  omap_gem_tiled_stride (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap (int,int) ; 
 struct omap_framebuffer* to_omap_framebuffer (struct drm_framebuffer*) ; 

void omap_framebuffer_update_scanout(struct drm_framebuffer *fb,
		struct drm_plane_state *state, struct omap_overlay_info *info)
{
	struct omap_framebuffer *omap_fb = to_omap_framebuffer(fb);
	const struct drm_format_info *format = omap_fb->format;
	struct plane *plane = &omap_fb->planes[0];
	u32 x, y, orient = 0;

	info->fourcc = fb->format->format;

	info->pos_x      = state->crtc_x;
	info->pos_y      = state->crtc_y;
	info->out_width  = state->crtc_w;
	info->out_height = state->crtc_h;
	info->width      = state->src_w >> 16;
	info->height     = state->src_h >> 16;

	/* DSS driver wants the w & h in rotated orientation */
	if (drm_rotation_90_or_270(state->rotation))
		swap(info->width, info->height);

	x = state->src_x >> 16;
	y = state->src_y >> 16;

	if (omap_gem_flags(fb->obj[0]) & OMAP_BO_TILED) {
		u32 w = state->src_w >> 16;
		u32 h = state->src_h >> 16;

		orient = drm_rotation_to_tiler(state->rotation);

		/*
		 * omap_gem_rotated_paddr() wants the x & y in tiler units.
		 * Usually tiler unit size is the same as the pixel size, except
		 * for YUV422 formats, for which the tiler unit size is 32 bits
		 * and pixel size is 16 bits.
		 */
		if (fb->format->format == DRM_FORMAT_UYVY ||
				fb->format->format == DRM_FORMAT_YUYV) {
			x /= 2;
			w /= 2;
		}

		/* adjust x,y offset for invert: */
		if (orient & MASK_Y_INVERT)
			y += h - 1;
		if (orient & MASK_X_INVERT)
			x += w - 1;

		/* Note: x and y are in TILER units, not pixels */
		omap_gem_rotated_dma_addr(fb->obj[0], orient, x, y,
					  &info->paddr);
		info->rotation_type = OMAP_DSS_ROT_TILER;
		info->rotation = state->rotation ?: DRM_MODE_ROTATE_0;
		/* Note: stride in TILER units, not pixels */
		info->screen_width  = omap_gem_tiled_stride(fb->obj[0], orient);
	} else {
		switch (state->rotation & DRM_MODE_ROTATE_MASK) {
		case 0:
		case DRM_MODE_ROTATE_0:
			/* OK */
			break;

		default:
			dev_warn(fb->dev->dev,
				"rotation '%d' ignored for non-tiled fb\n",
				state->rotation);
			break;
		}

		info->paddr         = get_linear_addr(fb, format, 0, x, y);
		info->rotation_type = OMAP_DSS_ROT_NONE;
		info->rotation      = DRM_MODE_ROTATE_0;
		info->screen_width  = fb->pitches[0];
	}

	/* convert to pixels: */
	info->screen_width /= format->cpp[0];

	if (fb->format->format == DRM_FORMAT_NV12) {
		plane = &omap_fb->planes[1];

		if (info->rotation_type == OMAP_DSS_ROT_TILER) {
			WARN_ON(!(omap_gem_flags(fb->obj[1]) & OMAP_BO_TILED));
			omap_gem_rotated_dma_addr(fb->obj[1], orient, x/2, y/2,
						  &info->p_uv_addr);
		} else {
			info->p_uv_addr = get_linear_addr(fb, format, 1, x, y);
		}
	} else {
		info->p_uv_addr = 0;
	}
}