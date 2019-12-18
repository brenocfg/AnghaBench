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
struct drm_device {struct atmel_hlcdc_dc* dev_private; } ;
struct drm_atomic_state {int dummy; } ;
struct atmel_hlcdc_dc_commit {int /*<<< orphan*/  work; struct drm_atomic_state* state; struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int pending; TYPE_2__ wait; } ;
struct atmel_hlcdc_dc {int /*<<< orphan*/  wq; TYPE_1__ commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_hlcdc_dc_atomic_complete (struct atmel_hlcdc_dc_commit*) ; 
 int /*<<< orphan*/  atmel_hlcdc_dc_atomic_work ; 
 int /*<<< orphan*/  drm_atomic_helper_cleanup_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int drm_atomic_helper_prepare_planes (struct drm_device*,struct drm_atomic_state*) ; 
 scalar_t__ drm_atomic_helper_swap_state (struct drm_atomic_state*,int) ; 
 int /*<<< orphan*/  drm_atomic_state_get (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  kfree (struct atmel_hlcdc_dc_commit*) ; 
 struct atmel_hlcdc_dc_commit* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_locked (TYPE_2__,int) ; 

__attribute__((used)) static int atmel_hlcdc_dc_atomic_commit(struct drm_device *dev,
					struct drm_atomic_state *state,
					bool async)
{
	struct atmel_hlcdc_dc *dc = dev->dev_private;
	struct atmel_hlcdc_dc_commit *commit;
	int ret;

	ret = drm_atomic_helper_prepare_planes(dev, state);
	if (ret)
		return ret;

	/* Allocate the commit object. */
	commit = kzalloc(sizeof(*commit), GFP_KERNEL);
	if (!commit) {
		ret = -ENOMEM;
		goto error;
	}

	INIT_WORK(&commit->work, atmel_hlcdc_dc_atomic_work);
	commit->dev = dev;
	commit->state = state;

	spin_lock(&dc->commit.wait.lock);
	ret = wait_event_interruptible_locked(dc->commit.wait,
					      !dc->commit.pending);
	if (ret == 0)
		dc->commit.pending = true;
	spin_unlock(&dc->commit.wait.lock);

	if (ret)
		goto err_free;

	/* We have our own synchronization through the commit lock. */
	BUG_ON(drm_atomic_helper_swap_state(state, false) < 0);

	/* Swap state succeeded, this is the point of no return. */
	drm_atomic_state_get(state);
	if (async)
		queue_work(dc->wq, &commit->work);
	else
		atmel_hlcdc_dc_atomic_complete(commit);

	return 0;

err_free:
	kfree(commit);
error:
	drm_atomic_helper_cleanup_planes(dev, state);
	return ret;
}