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
struct drm_mode_config_helper_funcs {int /*<<< orphan*/  (* atomic_commit_tail ) (struct drm_atomic_state*) ;} ;
struct TYPE_2__ {struct drm_mode_config_helper_funcs* helper_private; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_atomic_state {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_helper_commit_cleanup_done (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_tail (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_wait_for_dependencies (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_wait_for_fences (struct drm_device*,struct drm_atomic_state*,int) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  stub1 (struct drm_atomic_state*) ; 

__attribute__((used)) static void commit_tail(struct drm_atomic_state *old_state)
{
	struct drm_device *dev = old_state->dev;
	const struct drm_mode_config_helper_funcs *funcs;

	funcs = dev->mode_config.helper_private;

	drm_atomic_helper_wait_for_fences(dev, old_state, false);

	drm_atomic_helper_wait_for_dependencies(old_state);

	if (funcs && funcs->atomic_commit_tail)
		funcs->atomic_commit_tail(old_state);
	else
		drm_atomic_helper_commit_tail(old_state);

	drm_atomic_helper_commit_cleanup_done(old_state);

	drm_atomic_state_put(old_state);
}