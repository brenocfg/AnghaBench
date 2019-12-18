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
struct vc4_dev {int /*<<< orphan*/  async_modeset; } ;
struct drm_device {int dummy; } ;
struct drm_atomic_state {int legacy_cursor_update; int /*<<< orphan*/  commit_work; scalar_t__ async_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_work ; 
 int down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_atomic_helper_async_commit (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_cleanup_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int drm_atomic_helper_prepare_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int drm_atomic_helper_setup_commit (struct drm_atomic_state*,int) ; 
 scalar_t__ drm_atomic_helper_swap_state (struct drm_atomic_state*,int) ; 
 int drm_atomic_helper_wait_for_fences (struct drm_device*,struct drm_atomic_state*,int) ; 
 int /*<<< orphan*/  drm_atomic_state_get (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc4_atomic_complete_commit (struct drm_atomic_state*) ; 

__attribute__((used)) static int vc4_atomic_commit(struct drm_device *dev,
			     struct drm_atomic_state *state,
			     bool nonblock)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	int ret;

	if (state->async_update) {
		ret = down_interruptible(&vc4->async_modeset);
		if (ret)
			return ret;

		ret = drm_atomic_helper_prepare_planes(dev, state);
		if (ret) {
			up(&vc4->async_modeset);
			return ret;
		}

		drm_atomic_helper_async_commit(dev, state);

		drm_atomic_helper_cleanup_planes(dev, state);

		up(&vc4->async_modeset);

		return 0;
	}

	/* We know for sure we don't want an async update here. Set
	 * state->legacy_cursor_update to false to prevent
	 * drm_atomic_helper_setup_commit() from auto-completing
	 * commit->flip_done.
	 */
	state->legacy_cursor_update = false;
	ret = drm_atomic_helper_setup_commit(state, nonblock);
	if (ret)
		return ret;

	INIT_WORK(&state->commit_work, commit_work);

	ret = down_interruptible(&vc4->async_modeset);
	if (ret)
		return ret;

	ret = drm_atomic_helper_prepare_planes(dev, state);
	if (ret) {
		up(&vc4->async_modeset);
		return ret;
	}

	if (!nonblock) {
		ret = drm_atomic_helper_wait_for_fences(dev, state, true);
		if (ret) {
			drm_atomic_helper_cleanup_planes(dev, state);
			up(&vc4->async_modeset);
			return ret;
		}
	}

	/*
	 * This is the point of no return - everything below never fails except
	 * when the hw goes bonghits. Which means we can commit the new state on
	 * the software side now.
	 */

	BUG_ON(drm_atomic_helper_swap_state(state, false) < 0);

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
	 */

	drm_atomic_state_get(state);
	if (nonblock)
		queue_work(system_unbound_wq, &state->commit_work);
	else
		vc4_atomic_complete_commit(state);

	return 0;
}