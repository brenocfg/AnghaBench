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
struct omap_drm_private {int /*<<< orphan*/  dispc; TYPE_2__* dispc_ops; } ;
struct omap_crtc_state {scalar_t__ manually_updated; } ;
struct omap_crtc {int /*<<< orphan*/  channel; int /*<<< orphan*/  name; int /*<<< orphan*/  enabled; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_3__* dev; TYPE_4__* state; } ;
struct drm_color_lut {int dummy; } ;
struct TYPE_8__ {TYPE_1__* gamma_lut; scalar_t__ color_mgmt_changed; } ;
struct TYPE_7__ {int /*<<< orphan*/  event_lock; struct omap_drm_private* dev_private; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* mgr_go ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* mgr_set_gamma ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_color_lut*,unsigned int) ;} ;
struct TYPE_5__ {int length; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  omap_crtc_arm_event (struct drm_crtc*) ; 
 int /*<<< orphan*/  omap_crtc_flush (struct drm_crtc*) ; 
 int /*<<< orphan*/  omap_crtc_write_crtc_properties (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_color_lut*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 
 struct omap_crtc_state* to_omap_crtc_state (TYPE_4__*) ; 

__attribute__((used)) static void omap_crtc_atomic_flush(struct drm_crtc *crtc,
				   struct drm_crtc_state *old_crtc_state)
{
	struct omap_drm_private *priv = crtc->dev->dev_private;
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);
	struct omap_crtc_state *omap_crtc_state = to_omap_crtc_state(crtc->state);
	int ret;

	if (crtc->state->color_mgmt_changed) {
		struct drm_color_lut *lut = NULL;
		unsigned int length = 0;

		if (crtc->state->gamma_lut) {
			lut = (struct drm_color_lut *)
				crtc->state->gamma_lut->data;
			length = crtc->state->gamma_lut->length /
				sizeof(*lut);
		}
		priv->dispc_ops->mgr_set_gamma(priv->dispc, omap_crtc->channel,
					       lut, length);
	}

	omap_crtc_write_crtc_properties(crtc);

	/* Only flush the CRTC if it is currently enabled. */
	if (!omap_crtc->enabled)
		return;

	DBG("%s: GO", omap_crtc->name);

	if (omap_crtc_state->manually_updated) {
		/* send new image for page flips and modeset changes */
		spin_lock_irq(&crtc->dev->event_lock);
		omap_crtc_flush(crtc);
		omap_crtc_arm_event(crtc);
		spin_unlock_irq(&crtc->dev->event_lock);
		return;
	}

	ret = drm_crtc_vblank_get(crtc);
	WARN_ON(ret != 0);

	spin_lock_irq(&crtc->dev->event_lock);
	priv->dispc_ops->mgr_go(priv->dispc, omap_crtc->channel);
	omap_crtc_arm_event(crtc);
	spin_unlock_irq(&crtc->dev->event_lock);
}