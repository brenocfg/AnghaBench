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
struct intel_wakeref {int /*<<< orphan*/  work; int /*<<< orphan*/  mutex; TYPE_1__* ops; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_WAKEREF_BUG_ON (int /*<<< orphan*/ ) ; 
 int INTEL_WAKEREF_PUT_ASYNC ; 
 int /*<<< orphan*/  ____intel_wakeref_put_last (struct intel_wakeref*) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 

void __intel_wakeref_put_last(struct intel_wakeref *wf)
{
	INTEL_WAKEREF_BUG_ON(work_pending(&wf->work));

	/* Assume we are not in process context and so cannot sleep. */
	if (wf->ops->flags & INTEL_WAKEREF_PUT_ASYNC ||
	    !mutex_trylock(&wf->mutex)) {
		schedule_work(&wf->work);
		return;
	}

	____intel_wakeref_put_last(wf);
}