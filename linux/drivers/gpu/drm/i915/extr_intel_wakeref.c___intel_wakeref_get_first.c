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
struct intel_wakeref {int /*<<< orphan*/  count; int /*<<< orphan*/  mutex; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get ) (struct intel_wakeref*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_WAKEREF_BUG_ON (int) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpm_get (struct intel_wakeref*) ; 
 int /*<<< orphan*/  rpm_put (struct intel_wakeref*) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int stub1 (struct intel_wakeref*) ; 
 scalar_t__ unlikely (int) ; 

int __intel_wakeref_get_first(struct intel_wakeref *wf)
{
	/*
	 * Treat get/put as different subclasses, as we may need to run
	 * the put callback from under the shrinker and do not want to
	 * cross-contanimate that callback with any extra work performed
	 * upon acquiring the wakeref.
	 */
	mutex_lock_nested(&wf->mutex, SINGLE_DEPTH_NESTING);
	if (!atomic_read(&wf->count)) {
		int err;

		rpm_get(wf);

		err = wf->ops->get(wf);
		if (unlikely(err)) {
			rpm_put(wf);
			mutex_unlock(&wf->mutex);
			return err;
		}

		smp_mb__before_atomic(); /* release wf->count */
	}
	atomic_inc(&wf->count);
	mutex_unlock(&wf->mutex);

	INTEL_WAKEREF_BUG_ON(atomic_read(&wf->count) <= 0);
	return 0;
}