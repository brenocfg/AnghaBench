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
struct msm_pending_timer {int /*<<< orphan*/  timer; } ;
struct msm_kms {unsigned int pending_crtc_mask; TYPE_1__* funcs; int /*<<< orphan*/  commit_lock; struct msm_pending_timer* pending_timers; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct drm_crtc {int dummy; } ;
struct drm_atomic_state {struct drm_device* dev; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_commit ) (struct msm_kms*) ;int /*<<< orphan*/  (* complete_commit ) (struct msm_kms*,unsigned int) ;int /*<<< orphan*/  (* wait_flush ) (struct msm_kms*,unsigned int) ;int /*<<< orphan*/  (* flush_commit ) (struct msm_kms*,unsigned int) ;int /*<<< orphan*/  (* vsync_time ) (struct msm_kms*,struct drm_crtc*) ;int /*<<< orphan*/  (* prepare_commit ) (struct msm_kms*,struct drm_atomic_state*) ;int /*<<< orphan*/  (* enable_commit ) (struct msm_kms*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ can_do_async (struct drm_atomic_state*,struct drm_crtc**) ; 
 int /*<<< orphan*/  drm_atomic_helper_cleanup_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_hw_done (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_modeset_disables (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_modeset_enables (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_planes (struct drm_device*,struct drm_atomic_state*,int /*<<< orphan*/ ) ; 
 size_t drm_crtc_index (struct drm_crtc*) ; 
 unsigned int drm_crtc_mask (struct drm_crtc*) ; 
 unsigned int get_crtc_mask (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_to_ktime (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct msm_kms*) ; 
 int /*<<< orphan*/  stub2 (struct msm_kms*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (struct msm_kms*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  stub4 (struct msm_kms*,struct drm_crtc*) ; 
 int /*<<< orphan*/  stub5 (struct msm_kms*) ; 
 int /*<<< orphan*/  stub6 (struct msm_kms*,unsigned int) ; 
 int /*<<< orphan*/  stub7 (struct msm_kms*,unsigned int) ; 
 int /*<<< orphan*/  stub8 (struct msm_kms*,unsigned int) ; 
 int /*<<< orphan*/  stub9 (struct msm_kms*) ; 
 int /*<<< orphan*/  trace_msm_atomic_commit_tail_finish (int,unsigned int) ; 
 int /*<<< orphan*/  trace_msm_atomic_commit_tail_start (int,unsigned int) ; 
 int /*<<< orphan*/  trace_msm_atomic_flush_commit (unsigned int) ; 
 int /*<<< orphan*/  trace_msm_atomic_wait_flush_finish (unsigned int) ; 
 int /*<<< orphan*/  trace_msm_atomic_wait_flush_start (unsigned int) ; 

void msm_atomic_commit_tail(struct drm_atomic_state *state)
{
	struct drm_device *dev = state->dev;
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_kms *kms = priv->kms;
	struct drm_crtc *async_crtc = NULL;
	unsigned crtc_mask = get_crtc_mask(state);
	bool async = kms->funcs->vsync_time &&
			can_do_async(state, &async_crtc);

	trace_msm_atomic_commit_tail_start(async, crtc_mask);

	kms->funcs->enable_commit(kms);

	/*
	 * Ensure any previous (potentially async) commit has
	 * completed:
	 */
	trace_msm_atomic_wait_flush_start(crtc_mask);
	kms->funcs->wait_flush(kms, crtc_mask);
	trace_msm_atomic_wait_flush_finish(crtc_mask);

	mutex_lock(&kms->commit_lock);

	/*
	 * Now that there is no in-progress flush, prepare the
	 * current update:
	 */
	kms->funcs->prepare_commit(kms, state);

	/*
	 * Push atomic updates down to hardware:
	 */
	drm_atomic_helper_commit_modeset_disables(dev, state);
	drm_atomic_helper_commit_planes(dev, state, 0);
	drm_atomic_helper_commit_modeset_enables(dev, state);

	if (async) {
		struct msm_pending_timer *timer =
			&kms->pending_timers[drm_crtc_index(async_crtc)];

		/* async updates are limited to single-crtc updates: */
		WARN_ON(crtc_mask != drm_crtc_mask(async_crtc));

		/*
		 * Start timer if we don't already have an update pending
		 * on this crtc:
		 */
		if (!(kms->pending_crtc_mask & crtc_mask)) {
			ktime_t vsync_time, wakeup_time;

			kms->pending_crtc_mask |= crtc_mask;

			vsync_time = kms->funcs->vsync_time(kms, async_crtc);
			wakeup_time = ktime_sub(vsync_time, ms_to_ktime(1));

			hrtimer_start(&timer->timer, wakeup_time,
					HRTIMER_MODE_ABS);
		}

		kms->funcs->disable_commit(kms);
		mutex_unlock(&kms->commit_lock);

		/*
		 * At this point, from drm core's perspective, we
		 * are done with the atomic update, so we can just
		 * go ahead and signal that it is done:
		 */
		drm_atomic_helper_commit_hw_done(state);
		drm_atomic_helper_cleanup_planes(dev, state);

		trace_msm_atomic_commit_tail_finish(async, crtc_mask);

		return;
	}

	/*
	 * If there is any async flush pending on updated crtcs, fold
	 * them into the current flush.
	 */
	kms->pending_crtc_mask &= ~crtc_mask;

	/*
	 * Flush hardware updates:
	 */
	trace_msm_atomic_flush_commit(crtc_mask);
	kms->funcs->flush_commit(kms, crtc_mask);
	mutex_unlock(&kms->commit_lock);

	/*
	 * Wait for flush to complete:
	 */
	trace_msm_atomic_wait_flush_start(crtc_mask);
	kms->funcs->wait_flush(kms, crtc_mask);
	trace_msm_atomic_wait_flush_finish(crtc_mask);

	mutex_lock(&kms->commit_lock);
	kms->funcs->complete_commit(kms, crtc_mask);
	mutex_unlock(&kms->commit_lock);
	kms->funcs->disable_commit(kms);

	drm_atomic_helper_commit_hw_done(state);
	drm_atomic_helper_cleanup_planes(dev, state);

	trace_msm_atomic_commit_tail_finish(async, crtc_mask);
}