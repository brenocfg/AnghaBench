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
struct drm_crtc {TYPE_2__* primary; } ;
struct amdgpu_crtc {int /*<<< orphan*/ * connector; int /*<<< orphan*/ * encoder; int /*<<< orphan*/  pll_id; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_4__ {TYPE_1__* fb; } ;
struct TYPE_3__ {int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_PPLL_INVALID ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  dce_virtual_crtc_dpms (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (int /*<<< orphan*/ ) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dce_virtual_crtc_disable(struct drm_crtc *crtc)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

	dce_virtual_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
	if (crtc->primary->fb) {
		int r;
		struct amdgpu_bo *abo;

		abo = gem_to_amdgpu_bo(crtc->primary->fb->obj[0]);
		r = amdgpu_bo_reserve(abo, true);
		if (unlikely(r))
			DRM_ERROR("failed to reserve abo before unpin\n");
		else {
			amdgpu_bo_unpin(abo);
			amdgpu_bo_unreserve(abo);
		}
	}

	amdgpu_crtc->pll_id = ATOM_PPLL_INVALID;
	amdgpu_crtc->encoder = NULL;
	amdgpu_crtc->connector = NULL;
}