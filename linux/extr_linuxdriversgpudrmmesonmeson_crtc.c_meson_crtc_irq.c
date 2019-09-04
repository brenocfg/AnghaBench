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
struct TYPE_3__ {int osd1_commit; int /*<<< orphan*/  osd1_height; int /*<<< orphan*/  osd1_stride; int /*<<< orphan*/  osd1_addr; scalar_t__ osd1_interlace; int /*<<< orphan*/ * osd1_blk0_cfg; int /*<<< orphan*/  osd1_ctrl_stat; scalar_t__ osd1_enabled; } ;
struct meson_drm {TYPE_2__* drm; int /*<<< orphan*/  crtc; TYPE_1__ viu; scalar_t__ io_base; struct drm_plane* primary_plane; } ;
struct meson_crtc {int /*<<< orphan*/ * event; } ;
struct drm_rect {scalar_t__ y2; scalar_t__ x2; scalar_t__ y1; scalar_t__ x1; } ;
struct drm_plane_state {scalar_t__ crtc_h; scalar_t__ crtc_y; scalar_t__ crtc_w; scalar_t__ crtc_x; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_CANVAS_BLKMODE_LINEAR ; 
 int /*<<< orphan*/  MESON_CANVAS_ID_OSD1 ; 
 int /*<<< orphan*/  MESON_CANVAS_WRAP_NONE ; 
 int /*<<< orphan*/  VIU_OSD1_BLK0_CFG_W0 ; 
 int /*<<< orphan*/  VIU_OSD1_BLK0_CFG_W1 ; 
 int /*<<< orphan*/  VIU_OSD1_BLK0_CFG_W2 ; 
 int /*<<< orphan*/  VIU_OSD1_BLK0_CFG_W3 ; 
 int /*<<< orphan*/  VIU_OSD1_BLK0_CFG_W4 ; 
 int /*<<< orphan*/  VIU_OSD1_CTRL_STAT ; 
 int /*<<< orphan*/  VPP_MISC ; 
 int /*<<< orphan*/  VPP_OSD1_POSTBLEND ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_canvas_setup (struct meson_drm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_vpp_disable_interlace_vscaler_osd1 (struct meson_drm*) ; 
 int /*<<< orphan*/  meson_vpp_setup_interlace_vscaler_osd1 (struct meson_drm*,struct drm_rect*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct meson_crtc* to_meson_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void meson_crtc_irq(struct meson_drm *priv)
{
	struct meson_crtc *meson_crtc = to_meson_crtc(priv->crtc);
	unsigned long flags;

	/* Update the OSD registers */
	if (priv->viu.osd1_enabled && priv->viu.osd1_commit) {
		writel_relaxed(priv->viu.osd1_ctrl_stat,
				priv->io_base + _REG(VIU_OSD1_CTRL_STAT));
		writel_relaxed(priv->viu.osd1_blk0_cfg[0],
				priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W0));
		writel_relaxed(priv->viu.osd1_blk0_cfg[1],
				priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W1));
		writel_relaxed(priv->viu.osd1_blk0_cfg[2],
				priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W2));
		writel_relaxed(priv->viu.osd1_blk0_cfg[3],
				priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W3));
		writel_relaxed(priv->viu.osd1_blk0_cfg[4],
				priv->io_base + _REG(VIU_OSD1_BLK0_CFG_W4));

		/* If output is interlace, make use of the Scaler */
		if (priv->viu.osd1_interlace) {
			struct drm_plane *plane = priv->primary_plane;
			struct drm_plane_state *state = plane->state;
			struct drm_rect dest = {
				.x1 = state->crtc_x,
				.y1 = state->crtc_y,
				.x2 = state->crtc_x + state->crtc_w,
				.y2 = state->crtc_y + state->crtc_h,
			};

			meson_vpp_setup_interlace_vscaler_osd1(priv, &dest);
		} else
			meson_vpp_disable_interlace_vscaler_osd1(priv);

		meson_canvas_setup(priv, MESON_CANVAS_ID_OSD1,
			   priv->viu.osd1_addr, priv->viu.osd1_stride,
			   priv->viu.osd1_height, MESON_CANVAS_WRAP_NONE,
			   MESON_CANVAS_BLKMODE_LINEAR);

		/* Enable OSD1 */
		writel_bits_relaxed(VPP_OSD1_POSTBLEND, VPP_OSD1_POSTBLEND,
				    priv->io_base + _REG(VPP_MISC));

		priv->viu.osd1_commit = false;
	}

	drm_crtc_handle_vblank(priv->crtc);

	spin_lock_irqsave(&priv->drm->event_lock, flags);
	if (meson_crtc->event) {
		drm_crtc_send_vblank_event(priv->crtc, meson_crtc->event);
		drm_crtc_vblank_put(priv->crtc);
		meson_crtc->event = NULL;
	}
	spin_unlock_irqrestore(&priv->drm->event_lock, flags);
}