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
struct i915_timeline {int /*<<< orphan*/  requests; } ;
struct i915_request {TYPE_1__* timeline; int /*<<< orphan*/  link; TYPE_2__* engine; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ timeline; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void move_to_timeline(struct i915_request *request,
			     struct i915_timeline *timeline)
{
	GEM_BUG_ON(request->timeline == &request->engine->timeline);
	lockdep_assert_held(&request->engine->timeline.lock);

	spin_lock(&request->timeline->lock);
	list_move_tail(&request->link, &timeline->requests);
	spin_unlock(&request->timeline->lock);
}