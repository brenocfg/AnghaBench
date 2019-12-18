#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ingenic_drm {TYPE_5__* dma_hwdesc; int /*<<< orphan*/  map; int /*<<< orphan*/  pix_clk; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_framebuffer {TYPE_3__* format; } ;
struct drm_format_info {int dummy; } ;
struct TYPE_10__ {int clock; } ;
struct drm_crtc_state {struct drm_pending_vblank_event* event; TYPE_4__ adjusted_mode; int /*<<< orphan*/  mode; } ;
struct drm_crtc {TYPE_6__* dev; TYPE_2__* primary; struct drm_crtc_state* state; } ;
struct TYPE_12__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  next; } ;
struct TYPE_9__ {int /*<<< orphan*/  format; } ;
struct TYPE_8__ {TYPE_1__* state; } ;
struct TYPE_7__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_REG_LCD_DA0 ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 scalar_t__ drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  drm_crtc_arm_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 struct ingenic_drm* drm_crtc_get_priv (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 scalar_t__ drm_crtc_vblank_get (struct drm_crtc*) ; 
 struct drm_format_info* drm_format_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ingenic_drm_crtc_update_ctrl (struct ingenic_drm*,struct drm_format_info const*) ; 
 int /*<<< orphan*/  ingenic_drm_crtc_update_timings (struct ingenic_drm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ingenic_drm_crtc_atomic_flush(struct drm_crtc *crtc,
					  struct drm_crtc_state *oldstate)
{
	struct ingenic_drm *priv = drm_crtc_get_priv(crtc);
	struct drm_crtc_state *state = crtc->state;
	struct drm_pending_vblank_event *event = state->event;
	struct drm_framebuffer *drm_fb = crtc->primary->state->fb;
	const struct drm_format_info *finfo;

	if (drm_atomic_crtc_needs_modeset(state)) {
		finfo = drm_format_info(drm_fb->format->format);

		ingenic_drm_crtc_update_timings(priv, &state->mode);
		ingenic_drm_crtc_update_ctrl(priv, finfo);

		clk_set_rate(priv->pix_clk, state->adjusted_mode.clock * 1000);

		regmap_write(priv->map, JZ_REG_LCD_DA0, priv->dma_hwdesc->next);
	}

	if (event) {
		state->event = NULL;

		spin_lock_irq(&crtc->dev->event_lock);
		if (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		else
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	}
}