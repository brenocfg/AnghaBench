#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipu_soc {int dummy; } ;
struct ipu_crtc {int /*<<< orphan*/  di; int /*<<< orphan*/  dc; TYPE_1__* dev; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_3__* dev; TYPE_2__* state; } ;
struct TYPE_6__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/ * event; int /*<<< orphan*/  active; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct ipu_soc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  ipu_crtc_disable_planes (struct ipu_crtc*,struct drm_crtc_state*) ; 
 int /*<<< orphan*/  ipu_dc_disable (struct ipu_soc*) ; 
 int /*<<< orphan*/  ipu_dc_disable_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_prg_disable (struct ipu_soc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct ipu_crtc* to_ipu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void ipu_crtc_atomic_disable(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_crtc_state)
{
	struct ipu_crtc *ipu_crtc = to_ipu_crtc(crtc);
	struct ipu_soc *ipu = dev_get_drvdata(ipu_crtc->dev->parent);

	ipu_dc_disable_channel(ipu_crtc->dc);
	ipu_di_disable(ipu_crtc->di);
	/*
	 * Planes must be disabled before DC clock is removed, as otherwise the
	 * attached IDMACs will be left in undefined state, possibly hanging
	 * the IPU or even system.
	 */
	ipu_crtc_disable_planes(ipu_crtc, old_crtc_state);
	ipu_dc_disable(ipu);
	ipu_prg_disable(ipu);

	drm_crtc_vblank_off(crtc);

	spin_lock_irq(&crtc->dev->event_lock);
	if (crtc->state->event && !crtc->state->active) {
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = NULL;
	}
	spin_unlock_irq(&crtc->dev->event_lock);
}