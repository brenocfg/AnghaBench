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
struct msm_kms {TYPE_1__* funcs; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct drm_atomic_state {struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete_commit ) (struct msm_kms*,struct drm_atomic_state*) ;int /*<<< orphan*/  (* commit ) (struct msm_kms*,struct drm_atomic_state*) ;int /*<<< orphan*/  (* prepare_commit ) (struct msm_kms*,struct drm_atomic_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*) ; 
 int /*<<< orphan*/  drm_atomic_helper_cleanup_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_hw_done (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_modeset_disables (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_modeset_enables (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_planes (struct drm_device*,struct drm_atomic_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_atomic_wait_for_commit_done (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  stub1 (struct msm_kms*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  stub2 (struct msm_kms*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  stub3 (struct msm_kms*,struct drm_atomic_state*) ; 

void msm_atomic_commit_tail(struct drm_atomic_state *state)
{
	struct drm_device *dev = state->dev;
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_kms *kms = priv->kms;

	kms->funcs->prepare_commit(kms, state);

	drm_atomic_helper_commit_modeset_disables(dev, state);

	drm_atomic_helper_commit_planes(dev, state, 0);

	drm_atomic_helper_commit_modeset_enables(dev, state);

	if (kms->funcs->commit) {
		DRM_DEBUG_ATOMIC("triggering commit\n");
		kms->funcs->commit(kms, state);
	}

	msm_atomic_wait_for_commit_done(dev, state);

	kms->funcs->complete_commit(kms, state);

	drm_atomic_helper_commit_hw_done(state);

	drm_atomic_helper_cleanup_planes(dev, state);
}