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
struct intel_timeline {int /*<<< orphan*/  link; int /*<<< orphan*/  sync; int /*<<< orphan*/  requests; int /*<<< orphan*/  mutex; int /*<<< orphan*/  last_request; int /*<<< orphan*/  fence_context; int /*<<< orphan*/ * gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_ACTIVE_REQUEST (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_syncmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void mock_timeline_init(struct intel_timeline *timeline, u64 context)
{
	timeline->gt = NULL;
	timeline->fence_context = context;

	mutex_init(&timeline->mutex);

	INIT_ACTIVE_REQUEST(&timeline->last_request, &timeline->mutex);
	INIT_LIST_HEAD(&timeline->requests);

	i915_syncmap_init(&timeline->sync);

	INIT_LIST_HEAD(&timeline->link);
}