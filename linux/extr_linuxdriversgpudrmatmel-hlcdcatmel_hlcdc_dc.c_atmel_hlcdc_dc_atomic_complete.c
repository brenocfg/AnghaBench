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
struct atmel_hlcdc_dc_commit {struct drm_atomic_state* state; struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int pending; TYPE_2__ wait; } ;
struct atmel_hlcdc_dc {TYPE_1__ commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_helper_cleanup_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_modeset_disables (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_modeset_enables (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_helper_commit_planes (struct drm_device*,struct drm_atomic_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_helper_wait_for_vblanks (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  kfree (struct atmel_hlcdc_dc_commit*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all_locked (TYPE_2__*) ; 

__attribute__((used)) static void
atmel_hlcdc_dc_atomic_complete(struct atmel_hlcdc_dc_commit *commit)
{
	struct drm_device *dev = commit->dev;
	struct atmel_hlcdc_dc *dc = dev->dev_private;
	struct drm_atomic_state *old_state = commit->state;

	/* Apply the atomic update. */
	drm_atomic_helper_commit_modeset_disables(dev, old_state);
	drm_atomic_helper_commit_planes(dev, old_state, 0);
	drm_atomic_helper_commit_modeset_enables(dev, old_state);

	drm_atomic_helper_wait_for_vblanks(dev, old_state);

	drm_atomic_helper_cleanup_planes(dev, old_state);

	drm_atomic_state_put(old_state);

	/* Complete the commit, wake up any waiter. */
	spin_lock(&dc->commit.wait.lock);
	dc->commit.pending = false;
	wake_up_all_locked(&dc->commit.wait);
	spin_unlock(&dc->commit.wait.lock);

	kfree(commit);
}