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
struct vc4_dev {TYPE_1__* hvs; } ;
struct TYPE_4__ {scalar_t__ allocated; } ;
struct vc4_crtc_state {TYPE_2__ mm; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_helper_crtc_destroy_state (struct drm_crtc*,struct drm_crtc_state*) ; 
 int /*<<< orphan*/  drm_mm_remove_node (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_crtc_state* to_vc4_crtc_state (struct drm_crtc_state*) ; 
 struct vc4_dev* to_vc4_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_crtc_destroy_state(struct drm_crtc *crtc,
				   struct drm_crtc_state *state)
{
	struct vc4_dev *vc4 = to_vc4_dev(crtc->dev);
	struct vc4_crtc_state *vc4_state = to_vc4_crtc_state(state);

	if (vc4_state->mm.allocated) {
		unsigned long flags;

		spin_lock_irqsave(&vc4->hvs->mm_lock, flags);
		drm_mm_remove_node(&vc4_state->mm);
		spin_unlock_irqrestore(&vc4->hvs->mm_lock, flags);

	}

	drm_atomic_helper_crtc_destroy_state(crtc, state);
}