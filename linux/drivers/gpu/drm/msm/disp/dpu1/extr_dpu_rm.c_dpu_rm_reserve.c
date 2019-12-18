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
struct msm_display_topology {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {TYPE_3__ base; } ;
struct drm_crtc_state {TYPE_2__* crtc; } ;
struct dpu_rm_requirements {int dummy; } ;
struct dpu_rm {int /*<<< orphan*/  rm_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int _dpu_rm_make_reservation (struct dpu_rm*,struct drm_encoder*,struct drm_crtc_state*,struct dpu_rm_requirements*) ; 
 int _dpu_rm_populate_requirements (struct dpu_rm*,struct drm_encoder*,struct drm_crtc_state*,struct dpu_rm_requirements*,struct msm_display_topology) ; 
 int /*<<< orphan*/  _dpu_rm_release_reservation (struct dpu_rm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_crtc_needs_modeset (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int dpu_rm_reserve(
		struct dpu_rm *rm,
		struct drm_encoder *enc,
		struct drm_crtc_state *crtc_state,
		struct msm_display_topology topology,
		bool test_only)
{
	struct dpu_rm_requirements reqs;
	int ret;

	/* Check if this is just a page-flip */
	if (!drm_atomic_crtc_needs_modeset(crtc_state))
		return 0;

	DRM_DEBUG_KMS("reserving hw for enc %d crtc %d test_only %d\n",
		      enc->base.id, crtc_state->crtc->base.id, test_only);

	mutex_lock(&rm->rm_lock);

	ret = _dpu_rm_populate_requirements(rm, enc, crtc_state, &reqs,
					    topology);
	if (ret) {
		DPU_ERROR("failed to populate hw requirements\n");
		goto end;
	}

	ret = _dpu_rm_make_reservation(rm, enc, crtc_state, &reqs);
	if (ret) {
		DPU_ERROR("failed to reserve hw resources: %d\n", ret);
		_dpu_rm_release_reservation(rm, enc->base.id);
	} else if (test_only) {
		 /* test_only: test the reservation and then undo */
		DPU_DEBUG("test_only: discard test [enc: %d]\n",
				enc->base.id);
		_dpu_rm_release_reservation(rm, enc->base.id);
	}

end:
	mutex_unlock(&rm->rm_lock);

	return ret;
}