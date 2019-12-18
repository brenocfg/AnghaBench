#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_device {int dummy; } ;
struct drm_atomic_state {int /*<<< orphan*/  commit_work; scalar_t__ async_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_tail (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  commit_work ; 
 int /*<<< orphan*/  drm_atomic_helper_async_commit (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_cleanup_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int drm_atomic_helper_prepare_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int drm_atomic_helper_setup_commit (struct drm_atomic_state*,int) ; 
 int drm_atomic_helper_swap_state (struct drm_atomic_state*,int) ; 
 int drm_atomic_helper_wait_for_fences (struct drm_device*,struct drm_atomic_state*,int) ; 
 int /*<<< orphan*/  drm_atomic_state_get (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 

int drm_atomic_helper_commit(struct drm_device *dev,
			     struct drm_atomic_state *state,
			     bool nonblock)
{
	int ret;

	if (state->async_update) {
		ret = drm_atomic_helper_prepare_planes(dev, state);
		if (ret)
			return ret;

		drm_atomic_helper_async_commit(dev, state);
		drm_atomic_helper_cleanup_planes(dev, state);

		return 0;
	}

	ret = drm_atomic_helper_setup_commit(state, nonblock);
	if (ret)
		return ret;

	INIT_WORK(&state->commit_work, commit_work);

	ret = drm_atomic_helper_prepare_planes(dev, state);
	if (ret)
		return ret;

	if (!nonblock) {
		ret = drm_atomic_helper_wait_for_fences(dev, state, true);
		if (ret)
			goto err;
	}

	/*
	 * This is the point of no return - everything below never fails except
	 * when the hw goes bonghits. Which means we can commit the new state on
	 * the software side now.
	 */

	ret = drm_atomic_helper_swap_state(state, true);
	if (ret)
		goto err;

	/*
	 * Everything below can be run asynchronously without the need to grab
	 * any modeset locks at all under one condition: It must be guaranteed
	 * that the asynchronous work has either been cancelled (if the driver
	 * supports it, which at least requires that the framebuffers get
	 * cleaned up with drm_atomic_helper_cleanup_planes()) or completed
	 * before the new state gets committed on the software side with
	 * drm_atomic_helper_swap_state().
	 *
	 * This scheme allows new atomic state updates to be prepared and
	 * checked in parallel to the asynchronous completion of the previous
	 * update. Which is important since compositors need to figure out the
	 * composition of the next frame right after having submitted the
	 * current layout.
	 *
	 * NOTE: Commit work has multiple phases, first hardware commit, then
	 * cleanup. We want them to overlap, hence need system_unbound_wq to
	 * make sure work items don't artificially stall on each another.
	 */

	drm_atomic_state_get(state);
	if (nonblock)
		queue_work(system_unbound_wq, &state->commit_work);
	else
		commit_tail(state);

	return 0;

err:
	drm_atomic_helper_cleanup_planes(dev, state);
	return ret;
}