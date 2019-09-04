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
typedef  int /*<<< orphan*/  u64 ;
struct i915_timeline {int /*<<< orphan*/  link; int /*<<< orphan*/  sync; int /*<<< orphan*/  requests; int /*<<< orphan*/  last_request; int /*<<< orphan*/  lock; int /*<<< orphan*/  fence_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_syncmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_request_active (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void mock_timeline_init(struct i915_timeline *timeline, u64 context)
{
	timeline->fence_context = context;

	spin_lock_init(&timeline->lock);

	init_request_active(&timeline->last_request, NULL);
	INIT_LIST_HEAD(&timeline->requests);

	i915_syncmap_init(&timeline->sync);

	INIT_LIST_HEAD(&timeline->link);
}