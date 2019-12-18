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
struct drm_crtc_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {int /*<<< orphan*/  state; int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct armada_crtc {int update_pending; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  regs; int /*<<< orphan*/  regs_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUMB_FRAMEDONE_ENA ; 
 int /*<<< orphan*/  armada_drm_crtc_enable_irq (struct armada_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armada_drm_crtc_queue_state_event (struct drm_crtc*) ; 
 int /*<<< orphan*/  armada_drm_crtc_update_regs (struct armada_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armada_reg_queue_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_crtc_needs_modeset (int /*<<< orphan*/ ) ; 
 struct armada_crtc* drm_to_armada_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void armada_drm_crtc_atomic_flush(struct drm_crtc *crtc,
					 struct drm_crtc_state *old_crtc_state)
{
	struct armada_crtc *dcrtc = drm_to_armada_crtc(crtc);

	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	armada_reg_queue_end(dcrtc->regs, dcrtc->regs_idx);

	/*
	 * If we aren't doing a full modeset, then we need to queue
	 * the event here.
	 */
	if (!drm_atomic_crtc_needs_modeset(crtc->state)) {
		dcrtc->update_pending = true;
		armada_drm_crtc_queue_state_event(crtc);
		spin_lock_irq(&dcrtc->irq_lock);
		armada_drm_crtc_enable_irq(dcrtc, DUMB_FRAMEDONE_ENA);
		spin_unlock_irq(&dcrtc->irq_lock);
	} else {
		spin_lock_irq(&dcrtc->irq_lock);
		armada_drm_crtc_update_regs(dcrtc, dcrtc->regs);
		spin_unlock_irq(&dcrtc->irq_lock);
	}
}