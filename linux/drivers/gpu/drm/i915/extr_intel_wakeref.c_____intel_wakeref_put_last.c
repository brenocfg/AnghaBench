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
struct intel_wakeref {int /*<<< orphan*/  mutex; int /*<<< orphan*/  wakeref; TYPE_1__* ops; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put ) (struct intel_wakeref*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpm_put (struct intel_wakeref*) ; 
 int /*<<< orphan*/  stub1 (struct intel_wakeref*) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ____intel_wakeref_put_last(struct intel_wakeref *wf)
{
	if (!atomic_dec_and_test(&wf->count))
		goto unlock;

	/* ops->put() must reschedule its own release on error/deferral */
	if (likely(!wf->ops->put(wf))) {
		rpm_put(wf);
		wake_up_var(&wf->wakeref);
	}

unlock:
	mutex_unlock(&wf->mutex);
}