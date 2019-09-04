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
struct meson_plane {struct meson_drm* priv; } ;
struct TYPE_9__ {int osd1_ctrl_stat; int* osd1_blk0_cfg; int osd1_interlace; int /*<<< orphan*/  osd1_height; int /*<<< orphan*/  osd1_stride; int /*<<< orphan*/  osd1_addr; } ;
struct meson_drm {TYPE_5__* drm; TYPE_4__ viu; scalar_t__ io_base; } ;
struct drm_rect {int x1; int y1; int x2; int y2; } ;
struct drm_plane_state {int src_x; int src_y; int src_w; int src_h; int crtc_x; int crtc_y; int crtc_w; int crtc_h; TYPE_3__* crtc; struct drm_framebuffer* fb; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_gem_cma_object {int /*<<< orphan*/  paddr; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/ * pitches; TYPE_1__* format; } ;
struct TYPE_10__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_8__ {TYPE_2__ mode; } ;
struct TYPE_6__ {int format; } ;

/* Variables and functions */
#define  DRM_FORMAT_ARGB8888 131 
#define  DRM_FORMAT_RGB565 130 
#define  DRM_FORMAT_RGB888 129 
#define  DRM_FORMAT_XRGB8888 128 
 int DRM_MODE_FLAG_INTERLACE ; 
 int MESON_CANVAS_ID_OSD1 ; 
 int OSD_BLK0_ENABLE ; 
 int OSD_BLK_MODE_16 ; 
 int OSD_BLK_MODE_24 ; 
 int OSD_BLK_MODE_32 ; 
 int OSD_CANVAS_SEL ; 
 int OSD_COLOR_MATRIX_16_RGB565 ; 
 int OSD_COLOR_MATRIX_24_RGB ; 
 int OSD_COLOR_MATRIX_32_ARGB ; 
 int OSD_ENABLE ; 
 int OSD_ENDIANNESS_LE ; 
 int OSD_GLOBAL_ALPHA_SHIFT ; 
 int OSD_OUTPUT_COLOR_RGB ; 
 int /*<<< orphan*/  OSD_REPLACE_EN ; 
 int /*<<< orphan*/  VIU_OSD1_CTRL_STAT2 ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int fixed16_to_int (int) ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct meson_plane* to_meson_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_plane_atomic_update(struct drm_plane *plane,
				      struct drm_plane_state *old_state)
{
	struct meson_plane *meson_plane = to_meson_plane(plane);
	struct drm_plane_state *state = plane->state;
	struct drm_framebuffer *fb = state->fb;
	struct meson_drm *priv = meson_plane->priv;
	struct drm_gem_cma_object *gem;
	struct drm_rect src = {
		.x1 = (state->src_x),
		.y1 = (state->src_y),
		.x2 = (state->src_x + state->src_w),
		.y2 = (state->src_y + state->src_h),
	};
	struct drm_rect dest = {
		.x1 = state->crtc_x,
		.y1 = state->crtc_y,
		.x2 = state->crtc_x + state->crtc_w,
		.y2 = state->crtc_y + state->crtc_h,
	};
	unsigned long flags;

	/*
	 * Update Coordinates
	 * Update Formats
	 * Update Buffer
	 * Enable Plane
	 */
	spin_lock_irqsave(&priv->drm->event_lock, flags);

	/* Enable OSD and BLK0, set max global alpha */
	priv->viu.osd1_ctrl_stat = OSD_ENABLE |
				   (0xFF << OSD_GLOBAL_ALPHA_SHIFT) |
				   OSD_BLK0_ENABLE;

	/* Set up BLK0 to point to the right canvas */
	priv->viu.osd1_blk0_cfg[0] = ((MESON_CANVAS_ID_OSD1 << OSD_CANVAS_SEL) |
				      OSD_ENDIANNESS_LE);

	/* On GXBB, Use the old non-HDR RGB2YUV converter */
	if (meson_vpu_is_compatible(priv, "amlogic,meson-gxbb-vpu"))
		priv->viu.osd1_blk0_cfg[0] |= OSD_OUTPUT_COLOR_RGB;

	switch (fb->format->format) {
	case DRM_FORMAT_XRGB8888:
		/* For XRGB, replace the pixel's alpha by 0xFF */
		writel_bits_relaxed(OSD_REPLACE_EN, OSD_REPLACE_EN,
				    priv->io_base + _REG(VIU_OSD1_CTRL_STAT2));
		priv->viu.osd1_blk0_cfg[0] |= OSD_BLK_MODE_32 |
					      OSD_COLOR_MATRIX_32_ARGB;
		break;
	case DRM_FORMAT_ARGB8888:
		/* For ARGB, use the pixel's alpha */
		writel_bits_relaxed(OSD_REPLACE_EN, 0,
				    priv->io_base + _REG(VIU_OSD1_CTRL_STAT2));
		priv->viu.osd1_blk0_cfg[0] |= OSD_BLK_MODE_32 |
					      OSD_COLOR_MATRIX_32_ARGB;
		break;
	case DRM_FORMAT_RGB888:
		priv->viu.osd1_blk0_cfg[0] |= OSD_BLK_MODE_24 |
					      OSD_COLOR_MATRIX_24_RGB;
		break;
	case DRM_FORMAT_RGB565:
		priv->viu.osd1_blk0_cfg[0] |= OSD_BLK_MODE_16 |
					      OSD_COLOR_MATRIX_16_RGB565;
		break;
	};

	if (state->crtc->mode.flags & DRM_MODE_FLAG_INTERLACE) {
		priv->viu.osd1_interlace = true;

		dest.y1 /= 2;
		dest.y2 /= 2;
	} else
		priv->viu.osd1_interlace = false;

	/*
	 * The format of these registers is (x2 << 16 | x1),
	 * where x2 is exclusive.
	 * e.g. +30x1920 would be (1919 << 16) | 30
	 */
	priv->viu.osd1_blk0_cfg[1] = ((fixed16_to_int(src.x2) - 1) << 16) |
					fixed16_to_int(src.x1);
	priv->viu.osd1_blk0_cfg[2] = ((fixed16_to_int(src.y2) - 1) << 16) |
					fixed16_to_int(src.y1);
	priv->viu.osd1_blk0_cfg[3] = ((dest.x2 - 1) << 16) | dest.x1;
	priv->viu.osd1_blk0_cfg[4] = ((dest.y2 - 1) << 16) | dest.y1;

	/* Update Canvas with buffer address */
	gem = drm_fb_cma_get_gem_obj(fb, 0);

	priv->viu.osd1_addr = gem->paddr;
	priv->viu.osd1_stride = fb->pitches[0];
	priv->viu.osd1_height = fb->height;

	spin_unlock_irqrestore(&priv->drm->event_lock, flags);
}