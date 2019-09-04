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
struct TYPE_2__ {int /*<<< orphan*/  free_list; int /*<<< orphan*/  free_work; int /*<<< orphan*/  hw_ida; int /*<<< orphan*/  list; } ;
struct drm_i915_private {TYPE_1__ contexts; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  contexts_free_worker ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 

void mock_init_contexts(struct drm_i915_private *i915)
{
	INIT_LIST_HEAD(&i915->contexts.list);
	ida_init(&i915->contexts.hw_ida);

	INIT_WORK(&i915->contexts.free_work, contexts_free_worker);
	init_llist_head(&i915->contexts.free_list);
}