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
struct drm_crtc_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_2__* state; int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct armada_crtc {int /*<<< orphan*/  atomic_regs; int /*<<< orphan*/  regs; scalar_t__ regs_idx; } ;
struct TYPE_4__ {scalar_t__ color_mgmt_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armada_drm_update_gamma (struct drm_crtc*) ; 
 struct armada_crtc* drm_to_armada_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void armada_drm_crtc_atomic_begin(struct drm_crtc *crtc,
					 struct drm_crtc_state *old_crtc_state)
{
	struct armada_crtc *dcrtc = drm_to_armada_crtc(crtc);

	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	if (crtc->state->color_mgmt_changed)
		armada_drm_update_gamma(crtc);

	dcrtc->regs_idx = 0;
	dcrtc->regs = dcrtc->atomic_regs;
}