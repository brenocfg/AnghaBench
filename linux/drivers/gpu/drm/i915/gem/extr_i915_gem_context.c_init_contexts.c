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
struct TYPE_2__ {int /*<<< orphan*/  free_list; int /*<<< orphan*/  free_work; int /*<<< orphan*/  hw_id_list; int /*<<< orphan*/  hw_ida; int /*<<< orphan*/  list; int /*<<< orphan*/  mutex; } ;
struct drm_i915_private {TYPE_1__ contexts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ GEN11_MAX_CONTEXT_HW_ID ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ MAX_CONTEXT_HW_ID ; 
 int /*<<< orphan*/  contexts_free_worker ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_contexts(struct drm_i915_private *i915)
{
	mutex_init(&i915->contexts.mutex);
	INIT_LIST_HEAD(&i915->contexts.list);

	/* Using the simple ida interface, the max is limited by sizeof(int) */
	BUILD_BUG_ON(MAX_CONTEXT_HW_ID > INT_MAX);
	BUILD_BUG_ON(GEN11_MAX_CONTEXT_HW_ID > INT_MAX);
	ida_init(&i915->contexts.hw_ida);
	INIT_LIST_HEAD(&i915->contexts.hw_id_list);

	INIT_WORK(&i915->contexts.free_work, contexts_free_worker);
	init_llist_head(&i915->contexts.free_list);
}