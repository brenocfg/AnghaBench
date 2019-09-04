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
struct drm_crtc {int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct armada_crtc {int /*<<< orphan*/  atomic_regs; int /*<<< orphan*/  regs; scalar_t__ regs_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct armada_crtc* drm_to_armada_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void armada_drm_crtc_atomic_begin(struct drm_crtc *crtc,
					 struct drm_crtc_state *old_crtc_state)
{
	struct armada_crtc *dcrtc = drm_to_armada_crtc(crtc);

	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	dcrtc->regs_idx = 0;
	dcrtc->regs = dcrtc->atomic_regs;
}